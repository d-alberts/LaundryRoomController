#include <arduino.h>
#include "washerfsm.h"

const int machineCount = 2;

// Define pin numbering
int doorPins [machineCount] = {0, 1};
int lightPins [machineCount] = {0, 1};

// define the machines - :( wanted to do this in a loop but can't without using "new" (dynamic)
washerfsm machineArray [2] = {
  washerfsm( doorPins[1], lightPins[1] ),
  washerfsm( doorPins[2], lightPins[2] )
};

void setup() {
  Serial.begin(9600);
  

  // Construct machines
//  for (int i=0; i<machineCount; i++) {
//    machineArray [i] = washerfsm( doorPins[i], lightPins[i] );
//  }
//  
}

void loop() {
  MachineStates oldState [machineCount];
  // stores state at start of loop
  for (int i=0; i<machineCount; i++) {
    oldState[i] = machineArray[i].GetState();
  }



  machineArray[0].TurnOnLight();

  for (int i=0; i<machineCount; i++) {
  // sends messages for machine changes
    String machineName = String("M" + String(i));
    if ( (machineArray[i].GetState() != oldState [i]) || true ) {
      Serial.print(machineName);
      Serial.print(" ");
      Serial.println(machineArray[i].GetStateAsString());
    }
  
  
  }
delay(1000);
}



