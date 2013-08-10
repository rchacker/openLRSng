//Marc Griffith
//Use variable tone in tx.h to indicate rssi on bind.
//morse to indiicate start freq, sweep through the 256 rssi values and then morse to indicate end freq.
//replace this with the bind mode beep. 
//buzzerOn(2100 + (4 * RSSI_rx));
//create a power on sweep that only sweeps the hopping channels.

//dynamically change channel selection. large hopping list that is eliminated and then randomly culled and shuffled to bring down to required number of hops.
//there are 256 hopping channels available. min step size is 10kHz (1). max step size is 2.5MHz (255)
//each rssi value can be stored as a byte so only takes 256 bytes of ram.

 
//so for 915-928  //australia max 1W min 20 hopping channels
// available bandwidth 15MHz
// optimal step size  15000000/255 = 58823, 58kHz so step size of 5 or 6.


// for 472012500  ////australia max 100mW telemetry/control
//     472112500
//available bandwidth 100kHz
// so only 10 channels available at 10Khz step size (perhaps 9 to stay in limits)
// we can probably safely go up to 1W as we spread out by 10


//for 433050000  //australia max 25mW  up to 1W on 40 hops   100mw on 4 hops  50mW on 8 hops
//    443479000
// available bandwidth 10429kHz (10MHz)
//optimal step size 40898kHz (go with 4)


//Amateur advanced. up to 120W for rc to the moon. :o
//420-450
//available bandwidth 30Mhz
//optimal step size. 117kHz (11) or 12 minus some channels.

//perhaps use stl functions but then estimating ram usage is difficult:
//#include <vector>
//#include <algorithm> // sort, max_element, random_shuffle, remove_if, lower_bound


//with clear channel:
//Binary sketch size:  22196 bytes (of a 30720 byte maximum)
//Estimated SRAM used: 1628 bytes (of a 2048 byte maximum)

//without clear channel:
//Binary sketch size:  21714 bytes (of a 30720 byte maximum)
//Estimated SRAM used: 1373 bytes (of a 2048 byte maximum)

//so this code uses:
// 482 bytes FLASH, 255 bytes of sram. 


//need to modify for a variable channel pool depending on channel spacing and frequency range
const uint8_t CHANNEL_POOL = 40; //up to 255
uint8_t rssiReadings[CHANNEL_POOL];
//todo: save 255 sram by declaring this in randomizeClearChannel and passing into allocateHopchannels as a reference.
//but lets get it working first.


int8_t allocateHopchannels(uint8_t); //defined below.

void randomizeClearChannel(void)
{
  
  const uint8_t SAMPLE_SIZE = 255; //for larger sample sizes increase to 16 and 32bit.
  uint16_t rssiSum = 0;
  
  
  //keep this
  bind_data.rf_magic = 0;
  for (uint8_t h = 0; h < 4; h++) {
    bind_data.rf_magic = (bind_data.rf_magic << 8) + random(255);
  }
  
  //first scan through each channel like we do in the scanner code.
  
  //todo setup the module here...
  rfmSetCarrierFrequency(bind_data.rf_frequency);
  spiWriteRegister(0x7a, bind_data.rf_channel_spacing);   // channel spacing
  spiWriteRegister(0x1c, modem_params[bind_data.modem_params].r_1c); // r->r_1c  set IF filter bandwidth to match our data rate.
  to_rx_mode();
  
  for (uint8_t i = 0; i < CHANNEL_POOL; i++) {
    rssiSum = 0;
    rfmSetChannel(i);
    delay(1);
    for (uint8_t j = 0 ; j < SAMPLE_SIZE ; j++) {
      rssiSum += rfmGetRSSI(); //assuming 0 to 255
    }
    rssiReadings[i] = rssiSum / SAMPLE_SIZE;
  }
  
  //now calculate the max, min and average from all the readings.
  uint8_t Max_RSSI = 0;
  uint8_t Min_RSSI = 0;
  rssiSum = 0;
  
  for (uint8_t k =0; k < CHANNEL_POOL ; k++) {
    //buzzeron[rssi] to indicate rssi value?
    if (rssiReadings[k] > Max_RSSI)
      Max_RSSI = rssiReadings[k];
    else if (rssiReadings[k] < Min_RSSI) //perhaps drop the else
      Min_RSSI = rssiReadings[k];
    rssiSum += rssiReadings[k];
  }
  
  // yeah baby statistics http://en.wikipedia.org/wiki/Quartile
  
  uint16_t mean = rssiSum / CHANNEL_POOL;
    
  uint8_t quartile = (mean - Min_RSSI ) >> 1;
  
  uint8_t q3 = (Max_RSSI - mean) >> 1;
  
  if(!allocateHopchannels(quartile))
  {
    //fair amount of noise
    if(!allocateHopchannels(mean))
    {
      //more noise
      if(!allocateHopchannels(q3))
      {
        //pretty fucked now just go random.
        allocateHopchannels(CHANNEL_POOL);
      }
    }        
  }
}


//returns -1 on fail. 0 on success.
int8_t allocateHopchannels(uint8_t RSSI_threshold)
{
  //first check that we have enough channels.
  uint8_t thresholdCount = 0;
  for (uint8_t k =0; k < CHANNEL_POOL ; k++) {
    if(rssiReadings[k] < RSSI_threshold)
      thresholdCount++;
  }
  //otherwise this may never end..
  
  if (thresholdCount >= MAXHOPS)  //need to get proper hopcount from somewhere
  {
    return -1; //perhaps return number we were out by.
  }
  
  for (uint8_t c = 0; c < MAXHOPS; c++) {
  again:
    uint8_t ch = random(CHANNEL_POOL);
    if (rssiReadings[ch] > RSSI_threshold)
      goto again;
    
    // don't allow same channel twice
    for (uint8_t i = 0; i < c; i++) {
      if (bind_data.hopchannel[i] == ch) {
        goto again;
      }
    }
    
    bind_data.hopchannel[c] = ch;
  }
  return 0;
  
}







