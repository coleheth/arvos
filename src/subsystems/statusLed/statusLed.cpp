#include "statusLed.hpp"
#include <Arduino.h>

#define RED_PIN 10
#define BLUE_PIN 9
#define GREEN_PIN 11

#define LED_BRIGHTNESS 20 // Out of 255
#define LED_LIGHT_MIN_TIMING 500

unsigned long last_update;
unsigned long start_of_current_pattern;
bool has_run_pattern = false;
StatusLEDMode current_mode;

void StatusLEDSubsystem::setup()
{
    pinMode(RED_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);

    last_update = millis();
}

void updateMode(int i)
{
    if (i == 0)
        current_mode = OK;
    else if (i == 1)
        current_mode = LOOP_OVERRUN;
    else
        current_mode = UNKNOWN_ERROR;
}

void setColor(float r, float g, float b)
{
    analogWrite(RED_PIN, r * LED_BRIGHTNESS);
    analogWrite(BLUE_PIN, b * LED_BRIGHTNESS);
    analogWrite(GREEN_PIN, g * LED_BRIGHTNESS);
}

void StatusLEDSubsystem::loop()
{
    Event event;

    // deal with new patterns
    if (millis() - last_update > LED_LIGHT_MIN_TIMING)
    {
        if (popEvent(event, EventType::EVENT_STATUS_UPDATE))
        {
            updateMode(event.data);
            start_of_current_pattern = millis();
            has_run_pattern = true;
        }
        last_update = millis();
    }

    // deal with pattern
    if (current_mode == OK)
    {
        setColor(0, 1, 0);
    }
    else if (current_mode == LOOP_OVERRUN)
    {
        if ((millis() - start_of_current_pattern) % 500 < 250)
        {
            setColor(1, 0, 1);
        }
        else
        {
            setColor(0, 1, 1);
        }
    }
    else if (current_mode == UNKNOWN_ERROR)
    {
        setColor(1, 0, 0);
    }
}