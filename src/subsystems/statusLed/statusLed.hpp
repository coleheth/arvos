#pragma once
#include "../subsystem.hpp"
#include "../../core/event.hpp"
#include <Arduino.h>

enum StatusLEDMode {
    OK,
    UNKNOWN_ERROR,
    LOOP_OVERRUN
};

class StatusLEDSubsystem : public Subsystem {
    public:
        void setup() override;
        void loop() override;

    private:
        unsigned long lastToggle = 0;
        StatusLEDMode mode = OK;
};