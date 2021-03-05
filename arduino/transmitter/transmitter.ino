/*
  by Jarkko Saltiola (jasalt) 2021
*/

#include <VirtualWire.h>

int ledPin = 2;

void serial_setup(){
  Serial.begin(9600);
}

void setup(){
  vw_setup(2000); // bps
  serial_setup();
  pinMode(ledPin, OUTPUT);
}

char serialChar;

void test_loop(){
  while (Serial.available() > 0) {
    serialChar = Serial.read();
    digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
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
