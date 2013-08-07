  //##########################################################################################
  //Radiocommunications (Low Interference Potential Devices) Class Licence 2000
  //Federal Register of Legislative Instruments F2011C00543

  //item 52  Frequency hopping transmitters  915-928   Max EIRP 1W  A minimum of 20 hopping frequencies must be used.
  //Legal 1W LRS without an amateur licence!
  //ISM?

  //more notes from this document.
  //item 32A  Radiofrequency identification transmitters  920–926  Max 4W  A transmitter mentioned in this item must comply with ISO/IEC 18000-6c (RFID Gen. 2).
  //I doubt this complies as an identificaiton transmitter.
  
  //item 25   Telecommand or telemetry transmitters   472.0125–472.1125  max EIRP 100mW
  //we are good here, and at 1W if we use 10 channels.

  //item 17   All transmitters.  433.05 - 434.79  25mW
  //ISM band.

  //##########################################################################################
//#define RFMXX_915-928
//#define RFMXX_472
//#define RFMXX_433



  //###########################################################################################
  //Radiocommunications Licence Conditions (Amateur Licence) Determination No. 1 of 1997
  //Federal Register of Legislative Instruments F2010C00897

  //Australia amateur advanced 
  //420.000 MHz–450.000 MHz   Any emmission mode. 120W
  //keep in mind excluded frequency ranges below..
  //probably only legal way to use flytron 7W booster.

  //Australia amateur standard
  //430.000 MHz–450.000 MHz   Any emission mode with a necessary bandwidth no greater than 16 kHz  30W

  //Australia amateur foundation  10W
  //430.000 MHz–450.000 MHz   

//#define RFMXX_430-450

      //GFSK bandwidth is approx 100khz perhaps only advanced can use this band, certainly not foundation. (from datasheet, correct me if I am wrong)

      //Emission mode: 4K00J3E 
      //Necessary bandwidth no greater than 4 kHz
      //J Main carrier:  (a) is amplitude modulated; and (b) uses a single-sideband, suppressed carrier
      //3 Signal modulating the main carrier is a single channel containing analog information
      //E Telephony

      //Emission mode: 16K0F3E
      //Necessary bandwidth no greater than 16 kHz
      //F Main carrier: (a) is angle modulated; and (b) uses frequency modulation
      //3 Signal modulating the main carrier is a single channel containing analog information
      //E Telephony

      //Emission mode: 16K0G3E
      //Necessary bandwidth no greater than 16 kHz
      //G Main carrier: (a) is angle modulated; and (b) uses phase modulation
      //3 Signal modulating the main carrier is a single channel containing analog information
      //E Telephony



  //excluded frequency ranges:
  //New South Wales, the Australian Capital Territory and the Jervis Bay Territory
  //421.83125–421.99375 MHz 
  //425.25625–425.59375 MHz 
  //428.83125–428.99375 MHz

  //Melbourne Area
  //420.00–420.75 MHz 
  //421.25–424.75 MHz 
  //425.25–430.00 MHz

  //Perth Area
  //420 MHz–430 MHz

  //Sydney Area
  //421.25–421.75 MHz
  //428.25–428.75 MHz
  //########################################################################################



//USA
//Amateur  420-450
//Amateur  902-928
//ISM 
//433.050 - 434.790 
//866-868

