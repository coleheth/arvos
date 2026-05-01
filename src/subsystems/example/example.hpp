#pragma once
#include "../subsystem.hpp"
#include <Arduino.h>

// #include "../../core/event.hpp" // Uncomment this if need events



enum ExampleState
{
    EXAMPLE_RUNNING,
    EXAMPLE_NOT_RUNNING
};

class ExampleSubsystem : public Subsystem
{
public:
    void setup() override;
    void loop() override;

private:
    uint32_t state = EXAMPLE_RUNNING;
};