/*
   RadioLib SX127x Transmit Example

   This example transmits packets using SX1272 LoRa radio module.
   Each packet contains up to 256 bytes of data, in the form of:
    - Arduino String
    - null-terminated char array (C-string)
    - arbitrary binary data (byte array)

   Other modules from SX127x/RFM9x family can also be used.

   For default module settings, see the wiki page
   https://github.com/jgromes/RadioLib/wiki/Default-configuration#sx127xrfm9x---lora-modem

   For full API reference, see the GitHub Pages
   https://jgromes.github.io/RadioLib/
*/

// include the library
#include <RadioLib.h>
#define NUM_SENSORS     1       // Number of sensors to be received
#include "WeatherSensor.h"

// SX1272 has the following connections:
// NSS pin:   10
// DIO0 pin:  2
// RESET pin: 9
// DIO1 pin:  3
// #define PIN_RECEIVER_CS 17
// #define PIN_RECEIVER_IRQ 23
// #define PIN_RECEIVER_GPIO 23
//#define PIN_RECEIVER_RST 18


SX1272 radio = new Module(17, 23, 18, 23);

// or using RadioShield
// https://github.com/jgromes/RadioShield
//SX1272 radio = RadioShield.ModuleA;

void setup() {
  Serial.begin(115200);

  // initialize SX1272 with default settings
  Serial.print(F("[SX1272] Initializing ... "));
  int state = radio.beginFSK(868.3, 8.21, 57.136417, 250, 10, 32);
  uint8_t sync_word[] = {0xAA, 0x2D};
  state = radio.setSyncWord(sync_word, 2);


  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
  }

  // some modules have an external RF switch
  // controlled via two pins (RX enable, TX enable)
  // to enable automatic control of the switch,
  // call the following method
  // RX enable:   4
  // TX enable:   5
  /*
    radio.setRfSwitchPins(4, 5);
  */
}

void loop() {
  Serial.print(F("[SX1272] Transmitting packet ... "));

  // you can transmit C-string or Arduino string up to
  // 256 characters long
  // NOTE: transmit() is a blocking method!
  //       See example SX127x_Transmit_Interrupt for details
  //       on non-blocking transmission method.
  //int state = radio.transmit("Hello World!");
  // byte byteArr[] = {0x2DD4, 0x30, 0x38, 0x18, 0x80, 0x02, 0xC3, 0x18, 0xFF, 0xFF, 0xFF, 0x33, 0x28, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x9A, 0x7F};
  byte byteArr[] = {0x30, 0x38, 0x18, 0x80, 0x02, 0xC3, 0x18, 0xFF, 0xFF, 0xFF, 0x33, 0x28, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x9A, 0x7F};
  int state = radio.transmit(byteArr, 20);

  // you can also transmit byte array up to 256 bytes long
  /*
    byte byteArr[] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    int state = radio.transmit(byteArr, 8);
  */
  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("[SX1278] Packet transmitted successfully!"));
  } else if (state == RADIOLIB_ERR_PACKET_TOO_LONG) {
    Serial.println(F("[SX1278] Packet too long!"));
  } else if (state == RADIOLIB_ERR_TX_TIMEOUT) {
    Serial.println(F("[SX1278] Timed out while transmitting!"));
  } else {
    Serial.println(F("[SX1278] Failed to transmit packet, code "));
    Serial.println(state);
  }

  // wait for a second before transmitting again
  delay(2000);
}
