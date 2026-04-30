#include "event.hpp"

#define EVENT_QUEUE_SIZE 16

static Event queue[EVENT_QUEUE_SIZE];
static int head = 0;
static int tail = 0;

bool pushEvent(Event e) {
    int next = (head + 1) % EVENT_QUEUE_SIZE;
    if (next == tail) return false;
    
    queue[head] = e;
    head = next;
    return true;
}

bool popEvent(Event &e) {
    if (tail == head) return false;
    e = queue[tail];
    tail = (tail + 1) % EVENT_QUEUE_SIZE;
    return true;
}

bool popEvent(Event &e, EventType type) {
    if (tail == head || queue[tail].type != type) {
        e = {EVENT_NONE, 0};
        return false;
    }

    e = queue[tail];
    tail = (tail + 1) % EVENT_QUEUE_SIZE;
    return true;
}