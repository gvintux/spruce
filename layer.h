#ifndef LAYER_H
#define LAYER_H

#include "led.h"

class Layer {
public:
    Layer(int count);

    ~Layer();

    void addLedOnPin(int pin);

    void addLed(LED *led);

    void activate(int index, LED_CMD cmd);

    int getCount();

private:
    LED **leds;
    int count;
    int last;
};


#endif
