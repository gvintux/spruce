#ifndef STUBS_ARDUINO_H
#define STUBS_ARDUINO_H

#ifndef EMU

#define assert(EXPR)
#define REPORT(O, M, D)
typedef int I_MODE;

#include <Arduino.h>
#define I_MODE_CHANGE CHANGE
#define I_MODE_FALLING FALLING
#define I_MODE_RISING RISING

#endif


#endif
