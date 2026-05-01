#include "statusLed.hpp"
#include <Arduino.h>

void StatusLEDSubsystem::setColor(float r, float g, float b)
{
    analogWrite(RED_PIN, r * LED_BRIGHTNESS);
    analogWrite(BLUE_PIN, b * LED_BRIGHTNESS);
    analogWrite(GREEN_PIN, g * LED_BRIGHTNESS);
}

void StatusLEDSubsystem::setup()
{
    pinMode(RED_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);

    setColor(0, 0, 1);

    last_update = millis();
}

void StatusLEDSubsystem::updateFromQueue()
{
    Event event;

    if (popEvent(event, EventType::EVENT_STATUS_UPDATE))
    {
        state = event.data;
        start_of_current_pattern = millis();
        pattern_ran = false;
        pattern_ran_b = false;
    }
    last_update = millis();
}

void StatusLEDSubsystem::loop()
{
    if (millis() - last_update > UPDATE_INTERVAL)
        updateFromQueue();

    switch (state)
    {
    case SLED_SHOWING_OK:
        if (!pattern_ran)
        {
            setColor(0, 1, 0);
            pattern_ran = true;
        }
        break;

    case SLED_SHOWING_LOOP_OVERRUN:
        if ((millis() - start_of_current_pattern) % 500 < 250)
        {
            if (!pattern_ran)
            {
                setColor(1, 0, 1);
                pattern_ran = true;
                pattern_ran_b = false;
            }
        }
        else
        {
            if (!pattern_ran_b)
            {
                setColor(0, 1, 1);
                pattern_ran_b = true;
                pattern_ran = false;
            }
        }
        break;

    case SLED_SHOWING_GEN_ERROR:
        if (!pattern_ran)
        {
            setColor(1, 0, 0);
            pattern_ran = true;
        }
        break;

    } // end of switch btw
}