#ifdef EMU

#include <iostream>
#include <cassert>
#include "stubs.h"

#endif

#ifndef EMU

#define assert(EXPR)

#endif

#include "spruce.h"


Spruce::Spruce(int count) {
    assert(count > 0);
    this->count = count;
    this->last = 0;
    this->layers = new Layer *[count];
    assert(this->layers);
    program = P_INIT;
}

Spruce::~Spruce() {
    for (int i = 0; i < count; i++) delete layers[i];
    delete[] layers;
}

void Spruce::addLayer(Layer *layer) {
    assert(layer);
    assert(last < count);
    layers[last++] = layer;
    REPORT("spruce", "got layer", layer);
}

void Spruce::setProgram(String program) {
    assert(program.length() > 0);
    assert(isValid(program));
    this->program = program;
}

bool Spruce::isValid(String program) {
    return true;
}


void Spruce::exec() {
    int p_len = program.length();
    int i = 0;
    while (i < p_len) {
        LED_CMD state = LC_UNKNOW;
        state = (LED_CMD) program.c_str()[i];
        ++i;
        int start_idx = i;
        int layer_idx = -1;
        int LED_idx = -1;
        int layer_val = -1;
        int LED_val = -1;
        int d_val = 0;
        char c = '\0';
        switch (state) {
            case LC_ON:
            case LC_OFF:
            case LC_TOGGLE:
                while (i < p_len && isdigit(program.c_str()[i])) ++i;
#ifdef EMU
                layer_val = atoi(program.substr(start_idx, i).c_str());
#endif
#ifndef EMU
                layer_val = program.substring(start_idx, i).toInt();
#endif
                c = program.c_str()[i];
                if (c == ':') {
                    LED_idx = ++i;
                    while (i < p_len && isdigit(program.c_str()[i])) ++i;
#ifdef EMU
                    LED_val = atoi(program.substr(LED_idx, i).c_str());
#endif
#ifndef EMU
                    LED_val = program.substring(LED_idx, i).toInt();
#endif

                }
                if (LED_val > -1) layers[layer_val]->activate(LED_val, state);
                else {
                    for (int j = 0; j < layers[layer_val]->getCount(); j++) layers[layer_val]->activate(j, state);
                }
                break;
            case LC_DELAY:
                while (i < p_len && isdigit(program.c_str()[i])) ++i;
#ifdef EMU
                d_val = atoi(program.substr(start_idx, i).c_str());
#endif
#ifndef EMU
                d_val = program.substring(start_idx, i).toInt();
#endif
                delay(d_val);
                break;
        }

    }

}



