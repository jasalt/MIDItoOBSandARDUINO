// Wire radio transmitter, reads serial and passes data to radio towards receivers listening
// for given channel given as a character.
// Built on Arduino Micro Pro

// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
// Include dependant SPI Library 
#include <SPI.h> 
 
// Create Amplitude Shift Keying Object
RH_ASK rf_driver;
 
void setup()
{
    // Initialize ASK Object
    rf_driver.init();
    pinMode(13, OUTPUT);
    Serial.begin(9600);
}

char serialChar;

void loop_serial(){
  while (Serial.available() > 0) {
    serialChar = Serial.read();
    send(&serialChar);
  }
}

void loop(){
  loop_serial();
}

void send (char *message){
  rf_driver.send((uint8_t *)message, strlen(message));
  rf_driver.waitPacketSent();
  Serial.println("Sent: ");
  //Serial.println(String(uint8_t *)message);
}