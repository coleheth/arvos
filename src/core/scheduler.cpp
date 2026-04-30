#include "scheduler.hpp"

void Scheduler::addSubsystem(Subsystem* s) {
    if (count < MAX_SUBSYSTEMS) {
        subsystems[count++] = s;
    }
}

void Scheduler::setup() {
    for (int i = 0; i < count; i++) {
        subsystems[i]->setup();
    }
}

void Scheduler::loop() {
    for (int i = 0; i < count; i++) {
        subsystems[i]->loop();
    }
}