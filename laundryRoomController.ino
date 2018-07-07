#include <arduino.h>
#include "washerfsm.h"

const int machineCount = 2;

// Define pin numbering
int doorPins [machineCount] = {2, 1};
int lightPins [machineCount] = {0, 1};

// For switch debouncing
int lastDoorState[machineCount];
unsigned long switchStateLastChange[machineCount];
const unsigned int debounceDelay = 50;

// For other timing
unsigned long lastPrintTime = 0;
unsigned int printInterval = 1000;

// define the machines - :( wanted to do this in a loop but can't without using "new" (dynamic)
washerfsm machineArray [2] = {
  washerfsm( doorPins[1], lightPins[1] ),
  washerfsm( doorPins[2], lightPins[2] )
};

void setup() {
  Serial.begin(9600);
  for (int i=0; i<machineCount; i++) {
    pinMode(doorPins[i],INPUT_PULLUP);
  }
  

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

  // Check door switch status
  for (int i=0; i<machineCount; i++) {
    if ( lastDoorState[i] != digitalRead(doorPins[i]) ) {
      switchStateLastChange[i] = millis();
      lastDoorState[i] = !lastDoorState[i];
    }
    else if ( switchStateLastChange[i] + debounceDelay < millis() )
    {
      if ( lastDoorState[i] != machineArray[i].IsDoorOpen() ) { 
        if ( lastDoorState[i] == 1 ) { // switch closed
          machineArray[i].OpenDoor();
        } 
        else { 
          machineArray[i].CloseDoor();
        }
      }
    }
  }

  
  machineArray[0].TurnOnLight();

  if ( millis() - lastPrintTime > printInterval ) {
    lastPrintTime = lastPrintTime + printInterval;
    for (int i=0; i<machineCount; i++) {
      // sends messages for machine changes
      String machineName = String("M" + String(i));
      if ( (machineArray[i].GetState() != oldState [i]) || true ) {
        Serial.print(machineName);
        Serial.print(" ");
        Serial.println(machineArray[i].GetStateAsString());
      }
    }
  }
}



