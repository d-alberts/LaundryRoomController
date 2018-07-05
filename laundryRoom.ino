#include <arduino.h>
#include "washerfsm.h"

washerfsm washer1(1,2);
//washerfsm washer2(3,4);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("hi");
  Serial.println(washer1.GetState());
  delay(1000);
  washer1.TurnOnLight();
  Serial.println(washer1.GetState());
  delay(1000);
  washer1.TurnOffLight();
  Serial.println(washer1.GetState());
  delay(1000);
  washer1.OpenDoor();
  Serial.println(washer1.GetState());
  delay(1000);
  washer1.CloseDoor();
  Serial.println(washer1.GetState());
  delay(1000);
  
}

void loop() {

}
