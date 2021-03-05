/*
  by Jarkko Saltiola (jasalt)
*/

#include <VirtualWire.h>

int motorL = 12;
int motorR = 8;
int ledPin = 13;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as common motor control TODO
  pinMode(motorR, OUTPUT);
  pinMode(motorL, OUTPUT);

  // Radio receiver
  Serial.begin(9600);
  Serial.println("Device is ready");
  vw_setup(2000); //bps
  vw_rx_start();
}

// the loop function runs over and over again forever
int controlVal;

void motor_controller(char controlChar){
  controlVal = controlChar - 48; // TODO fix this properly

  Serial.print("Got: ");
  Serial.println(String(controlVal));

  switch (controlVal){
  case 0:
    digitalWrite(motorL, HIGH);
    digitalWrite(motorR, HIGH);
    Serial.println("Forward");

    break;
  case 1:
    digitalWrite(motorR, HIGH);
    Serial.println("Left");

    break;
  case 2:
    digitalWrite(motorL, HIGH);
    Serial.println("Right");

    break;
  default:
    digitalWrite(ledPin, HIGH);
    Serial.println("ERROR: Odd value!");
  }

  delay(300);

  digitalWrite(motorL, LOW);
  digitalWrite(motorR, LOW);
  digitalWrite(13, LOW);
}

void loop() {
  byte message[VW_MAX_MESSAGE_LEN];
  byte messageLength = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(message, &messageLength)){
    for (int i = 0; i < messageLength; i++){
      //Serial.write(message[i]);
      motor_controller(message[i]);
      //delay(10);
    }
  }

  else {
    digitalWrite(ledPin, HIGH);
    delay(50);
    digitalWrite(ledPin, LOW);
  }

}
