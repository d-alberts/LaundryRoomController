#ifndef WASHERFSM_H
#define WASHERFSM_H

#include <Arduino.h>

enum MachineStates { isEmpty, isRunning, isPaused, isFull, maxStates };
enum MachineEvents { turnOnLight, turnOffLight, openDoor, closeDoor, maxEvents };

class washerfsm {
    public:
        washerfsm();
        washerfsm(int lightPin, int doorPin);

        void TurnOnLight();
        void TurnOffLight();
        void OpenDoor();
        void CloseDoor();
        bool IsLightOn();
        bool IsDoorOpen();

        MachineStates GetState();
        String GetStateAsString();
        long int GetLastCycleTime();
        
        long int lastCycleTime;
        long int startTime;
                
    private:
        int _lightPin;
        int _doorPin;

        bool _lightOn;
        bool _doorOpen;
        
        enum MachineStates currentState;
        // enum MachineEvents newEvent;
        
        void SendEvent(enum MachineEvents);
        void Action_isEmpty_turnOnLight();
        void Action_isEmpty_turnOffLight();
        void Action_isEmpty_openDoor();
        void Action_isEmpty_closeDoor();
        void Action_isRunning_turnOnLight();
        void Action_isRunning_turnOffLight();
        void Action_isRunning_openDoor();
        void Action_isRunning_closeDoor();
        void Action_isPaused_turnOnLight();
        void Action_isPaused_turnOffLight();
        void Action_isPaused_openDoor();
        void Action_isPaused_closeDoor();
        void Action_isFull_turnOnLight();
        void Action_isFull_turnOffLight();
        void Action_isFull_openDoor();
        void Action_isFull_closeDoor();
        
        
        void (*washerfsm::*stateTable [maxStates] [maxEvents]) ();
        
};

#endif
