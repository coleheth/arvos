#include <Arduino.h>
#include "core/scheduler.hpp"
#include "subsystems/statusLed/statusLed.hpp"

#define ALLOWED_LOOP_MS 500

Scheduler scheduler;
StatusLEDSubsystem statusLed;

unsigned long last_loop;
bool was_last_loop_overrun = false;

void setup()
{
  scheduler.addSubsystem(&statusLed);
  scheduler.setup();

  Event event = Event{EVENT_STATUS_UPDATE, 0};
  pushEvent(event);

  last_loop = millis();
}

void loop()
{
  scheduler.loop();

  unsigned long now = millis();
  if (now - last_loop > ALLOWED_LOOP_MS) {
    pushEvent(Event{EVENT_STATUS_UPDATE, 0});
    was_last_loop_overrun = true;
  } else if (was_last_loop_overrun) {
    was_last_loop_overrun = false;
    pushEvent(Event{EVENT_STATUS_UPDATE, 1});
  }
  last_loop = now;
}