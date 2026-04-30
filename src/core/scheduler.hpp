#pragma once
#include "subsystems/subsystem.hpp"

#define MAX_SUBSYSTEMS 8

class Scheduler {
    public:
        void addSubsystem(Subsystem* s);
        void setup();
        void loop();

    private:
        Subsystem* subsystems[MAX_SUBSYSTEMS];
        int count = 0;
};