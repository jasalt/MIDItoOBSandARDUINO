// Wire radio receiver, waiting for signal with a character indicating device "channel"
// blinks red led when receives message for associated channel.
// Built on Arduino Mini Pro

// ref https://lastminuteengineers.com/433mhz-rf-wireless-arduino-tutorial/#arduino-code-for-433mhz-rf-receiver

// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
// Include dependant SPI Library 
#include <SPI.h> 
 
// Create Amplitude Shift Keying Object

// Params: speed/rxpin/txpin/pttinverted
// https://www.airspayce.com/mikem/arduino/RadioHead/classRH__ASK.html
// Set RX to pin 10 of Arduino Mini Pro
// pttinverted not tested with other values but worked like so

RH_ASK rf_driver(2000, 10, 11,5);  

int ledPin = 2;

void setup()
{
    // Initialize ASK Object
    rf_driver.init();
    // Setup Serial Monitor
    Serial.begin(9600);
    pinMode(ledPin, OUTPUT);
}

const char chan = '1';  // Receiver channel. Set before flashing.

void loop()
{
    // Set buffer to size of expected message
    uint8_t buf[1];
    uint8_t buflen = sizeof(buf);
    
    // Check if received packet is correct size
    if (rf_driver.recv(buf, &buflen)) {
      Serial.print("Message Received: ");
      Serial.println((char*)buf);

     if ((char)buf[0] == chan) {
      Serial.println("Activating led");
      digitalWrite(ledPin, HIGH);
      delay(1000);
     } 
  }
  digitalWrite(ledPin, LOW);
}
