#ifdef EMU

#include <cassert>
#include "stubs.h"

#endif

#include "layer.h"


Layer::Layer(int count) {
    this->count = count;
    this->leds = new LED *[count];
    this->last = 0;
    assert(this->leds != NULL);
}

Layer::~Layer() {
    for (int i = 0; i < count; i++) delete leds[i];
    delete[] leds;
}

void Layer::addLedOnPin(int pin) {
    assert(pin > 0);
    assert(last < count);
    LED *led = new LED(pin);
    assert(led);
    leds[last++] = led;
    REPORT(this, "layer got LED", pin);
}

void Layer::addLed(LED *led) {
    assert(led);
    assert(last < count);
    leds[last++] = led;
}

void Layer::activate(int index, LED_CMD cmd) {
    assert(index >= -1);
    assert(cmd != LC_UNKNOW);
    switch (cmd) {
        case LC_ON:
            leds[index]->on();
            break;
        case LC_OFF:
            leds[index]->off();
            break;
        case LC_TOGGLE:
            leds[index]->toggle();
            break;
    }
}

int Layer::getCount() {
    return count;
}
