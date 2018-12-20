#ifndef SPRUCE_BUTTON_H
#define SPRUCE_BUTTON_H

#ifdef EMU

#include "stubs.h"

#endif

#ifndef EMU

#include "stubs_arduino.h"

#endif

typedef void (*ButtonHandler)();

class Button {
public:
    Button(int pin, bool pullup);

    void setHandler(ButtonHandler handler);

    int getState();

    int readState();

    void handle();

    void attachInterrupt(I_MODE type);

private:
    ButtonHandler handler;
    int pin;
    int state;
};


#endif
