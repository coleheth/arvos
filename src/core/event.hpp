#pragma once
#include <stdint.h>

enum EventType {
    EVENT_NONE,
    EVENT_TICK,
    EVENT_SERIAL_RX,
    EVENT_STATUS_UPDATE
};

struct Event {
    EventType type;
    uint32_t data;
};

bool pushEvent(Event e);
bool popEvent(Event &e);
bool popEvent(Event &e, EventType type);
