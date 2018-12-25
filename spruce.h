#ifndef SPRUCE_H
#define SPRUCE_H

#include "layer.h"

#ifdef EMU

#include "stubs.h"

#endif

#ifndef EMU

#include <Arduino.h>

#endif
static const String P_RESET = "L3L2L1L0";

static const String P_INIT = "H3H21H0D2000";

class Spruce {
public:
    Spruce(int count); 

    ~Spruce();

    void addLayer(Layer *layer);

    void setProgram(String program);

    void exec();

    static bool isValid(String program);
    
private:
    Layer **layers;
    String program;
    int count;
    int last;
};

#endif


