#pragma once
#include "../subsystem.hpp"
#include "../../core/event.hpp"
#include <Arduino.h>

#define RED_PIN 10
#define BLUE_PIN 9
#define GREEN_PIN 11

#define LED_BRIGHTNESS 20 // Out of 255

#define UPDATE_INTERVAL 500

enum StatusLEDState
{
    SLED_SHOWING_OK,
    SLED_SHOWING_LOOP_OVERRUN,
    SLED_SHOWING_GEN_ERROR
};

class StatusLEDSubsystem : public Subsystem
{
public:
    void setup() override;
    void loop() override;

private:
    void updateFromQueue();
    void setColor(float r, float g, float b);

    uint32_t state = SLED_SHOWING_OK;

    unsigned long last_update = 0;
    unsigned long start_of_current_pattern;

    bool pattern_ran = false;
    bool pattern_ran_b = false;
};