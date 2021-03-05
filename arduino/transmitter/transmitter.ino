/*
  by Jarkko Saltiola (jasalt) 2021
  Using Arduino Pro Micro, has micro usb with serial, easy to hook up to laptop running MIDItoOBS.
  RFS1000A radio connected to PIN 10
*/

#include <VirtualWire.h>

int ledPin = 2;

void serial_setup(){
  Serial.begin(9600);
}

void setup(){
  vw_set_tx_pin(10);
  vw_setup(2000);
  serial_setup();
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
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx();
  Serial.println("Sent: ");
  //Serial.println(String(uint8_t *)message);
}
