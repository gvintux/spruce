#ifndef STUBS_H
#define STUBS_H

#ifdef EMU

#include <iostream>
#include <unistd.h>

using namespace std;

#define OUTPUT 0
#define INPUT 1
#define INPUT_PULLUP 2
#define HIGH 1
#define LOW 0
#define REPORT(O, M, D)  {cerr << (O) << ": " << (M) << " [" << (D) << "]" << endl;}
typedef string String;

typedef void (*ISR_FUNC)();

typedef enum {
    I_MODE_CHANGE, I_MODE_RISING, I_MODE_FALLING
} I_MODE;

static const String I_MODE_DESC[] = {"CHANGE", "RISING", "FALLING"};

static void digitalWrite(int pin, int state) {
    REPORT(pin, "state", state == HIGH ? "o" : "x");
}

static int digitalRead(int pin) {
    srand(time(NULL));
    int state = rand() % 2;
    REPORT(pin, "read state", state == HIGH ? "o" : "x");
    return state;
}


static void pinMode(int pin, int mode) {
    REPORT(pin, "mode", mode == OUTPUT ? "OUT" : "IN");
}

static void delay(int msec) {
    usleep(msec * 1000);
    REPORT("sys", "delay", msec);
}

static int digitalPinToInterrupt(int interruptPin) {
    return interruptPin;

}

static void attachInterrupt(int pin, ISR_FUNC ISR, I_MODE mode) {
    REPORT(pin, "interrupt attached by mode", I_MODE_DESC[mode]);
}

#endif

#endif
