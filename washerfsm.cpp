#include "Arduino.h"
#include "washerfsm.h"

// Transition events and transition table

void washerfsm::Action_isEmpty_turnOnLight (void) {
  // Machine start
  Serial.println("starting...");
  currentState = isRunning;
  startTime = millis();
}

void washerfsm::Action_isEmpty_turnOffLight (void) {
  // Dummy event
}
void washerfsm::Action_isEmpty_openDoor (void) {
  // No state change
}
void washerfsm::Action_isEmpty_closeDoor (void) {
  // No state change
}
void washerfsm::Action_isRunning_turnOnLight (void) {
  // Dummy event
}
void washerfsm::Action_isRunning_turnOffLight (void) {
  // Cycle complete
  currentState = isFull;
  lastCycleTime = ( millis() - startTime );
}
void washerfsm::Action_isRunning_openDoor (void) {
  // Cycle pause
  currentState = isPaused;
}
void washerfsm::Action_isRunning_closeDoor (void) {
  // Dummy event
}
void washerfsm::Action_isPaused_turnOnLight (void) {
  // Dummy event
}
void washerfsm::Action_isPaused_turnOffLight (void) {
  // Cycle cancelled?
}
void washerfsm::Action_isPaused_openDoor (void) {
  // Non-event
}
void washerfsm::Action_isPaused_closeDoor (void) {
  // Cycle resumes
  currentState = isRunning;
}
void washerfsm::Action_isFull_turnOnLight (void) {
  // Start cycle (2nd round?)
  currentState = isRunning;
}
void washerfsm::Action_isFull_turnOffLight (void) {
  // Dummy event
}
void washerfsm::Action_isFull_openDoor (void) {
  // Machine emptied
  // unless someone just opens the door to check :(
  currentState = isEmpty; 
}
void washerfsm::Action_isFull_closeDoor (void) {
  // Dummy Event
}

washerfsm::washerfsm(int lightPin, int doorPin) {
  _lightPin = lightPin;
  _doorPin = doorPin;
  //currentState = isEmpty;
}


// Event-driven state changes
void washerfsm::SendEvent (enum MachineEvents newEvent) {
  void ( washerfsm::*stateTable [maxStates] [maxEvents] ) () = {
    { &washerfsm::Action_isEmpty_turnOnLight, &washerfsm::Action_isEmpty_turnOffLight, &washerfsm::Action_isEmpty_openDoor, &washerfsm::Action_isEmpty_closeDoor },
    { &washerfsm::Action_isRunning_turnOnLight, &washerfsm::Action_isRunning_turnOffLight, &washerfsm::Action_isRunning_openDoor, &washerfsm::Action_isRunning_closeDoor },
    { &washerfsm::Action_isPaused_turnOnLight, &washerfsm::Action_isPaused_turnOffLight, &washerfsm::Action_isPaused_openDoor, &washerfsm::Action_isPaused_closeDoor },
    { &washerfsm::Action_isFull_turnOnLight, &washerfsm::Action_isFull_turnOffLight, &washerfsm::Action_isFull_openDoor, &washerfsm::Action_isFull_closeDoor }
};
  //void (washerfsm::*stateTable)(void) = &washerfsm::Action_isEmpty_turnOnLight;
  if ((( newEvent >= 0 ) && ( newEvent < maxEvents )) && ((currentState >= 0 ) && (currentState < maxStates))) {
    (this->*stateTable[currentState][newEvent]) (); 
  }
  else {
    // ouch
  }
}


String washerfsm::GetState(){
  
  switch (currentState) {
    case isEmpty:
      return "empty";
      break;
    case isRunning:
      return "running";
      break;
    case isPaused:
      return "paused";
      break;
    case isFull:
      return "full";
      break;
    default:
      return "ugh";
  }
}  

long int washerfsm::GetLastCycleTime() {
  return lastCycleTime;
}

void washerfsm::TurnOnLight() { 
  SendEvent(turnOnLight);
}
void washerfsm::TurnOffLight() {
  SendEvent(turnOffLight);
}
void washerfsm::OpenDoor() {
  SendEvent(openDoor);
}
void washerfsm::CloseDoor() {
  SendEvent(closeDoor);
}


