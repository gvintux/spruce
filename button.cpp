#ifdef EMU

#include <cassert>
#include "stubs.h"

#endif

#ifndef EMU

#include <Arduino.h>
typedef int I_MODE;

#endif

#include "button.h"

Button::Button(int pin, bool pullup) {
    assert(pin > -1);
    this->pin = pin;
    if (pullup) pinMode(pin, INPUT_PULLUP);
    else pinMode(pin, INPUT);
    this->state = readState();
}

void Button::setHandler(ButtonHandler handler) {
    assert(handler);
    this->handler = handler;
}

void Button::attachInterrupt(I_MODE type) {
    ::attachInterrupt(digitalPinToInterrupt(pin), handler, type);
}

int Button::getState() {
    return state;
}

int Button::readState() {
    state = digitalRead(pin);
    return state;
}

void Button::handle() {
    if (readState() == HIGH) handler();
}


