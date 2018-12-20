#include "led.h"

#ifdef EMU

#include <cassert>
#include "stubs.h"

#endif


LED::LED(int pin) {
    assert(pin > -1);
    this->pin = pin;
    pinMode(pin, OUTPUT);
    off();
}

LED::~LED() {
    off();
}

void LED::on() {
#ifndef EMU
    if (state == HIGH) return;
#endif
    state = HIGH;
    digitalWrite(pin, state);
}

void LED::off() {
#ifndef EMU
    if (state == LOW) return;
#endif
    state = LOW;
    digitalWrite(pin, state);
}

int LED::toggle() {
    if (state == LOW) on();
    else off();
    return state;
}

int LED::getPin() {
    return pin;
}

int LED::getState() {
    return state;
}