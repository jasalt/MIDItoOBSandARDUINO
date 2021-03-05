/*
  by Jarkko Saltiola (jasalt) 2021
  Arduino Pro Micro, does not have led on pin 13 like UNO, but TXLED can be controlled 
  with TXLED1; and TXLED0; commands in way that I did not fully understand but made 
  work good enough for now.
*/

#include <VirtualWire.h>

int ledPin = 2;

void serial_setup(){
  Serial.begin(9600);
}

void setup(){
  vw_setup(2000);
  serial_setup();
  TXLED1;
}

char serialChar;

void test_loop(){
  while (Serial.available() > 0) {
    serialChar = Serial.read();
    TXLED1; // Blinks the led
  }
}

void serial_control(){
  while (Serial.available() > 0) {
    serialChar = Serial.read();
    send(&serialChar);
  }
}

void loop(){
  test_loop();
  //serial_control();
}
void send (char *message){
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx();
  Serial.println("Sent: ");
  //Serial.println(String(uint8_t *)message);
}
