#ifdef EMU

#include <iostream>
#include <cctype>
#include <cstdlib>
#include <csignal>
#include <cassert>
#include "stubs.h"

using namespace std;

static void setup();

static void loop();

static void change_mode();

static void interrupt_sig(int signal);

#endif

#include "led.h"
#include "layer.h"
#include "spruce.h"
#include "button.h"

#ifndef EMU

#include "stubs_arduino.h"

#endif

const int LAYERS = 4;
const int l0p0 = 1;
const int l1p0 = 2;
const int l1p1 = 3;
const int l2p0 = 4;
const int l2p1 = 5;
const int l3p0 = 6;
const int l3p1 = 7;


static const String P0 = "T3D1000T2D1000T1D1000T0D1000";
static const String P1 = "H3D1000H2D1000H1D1000H0D1000";
static const String P2 = "L3D1000L2D1000L1D1000L0D1000";
static const String programs[] = {P0, P1, P2};
static const int P_COUNT = 3;
static int p_index = 0;
static const int MODE_PIN = 2;
static const int LOVE_PIN = 4;


static Spruce *s = new Spruce(LAYERS);
static Button *modeButton = new Button(MODE_PIN, true);
static Button *loveButton = new Button(LOVE_PIN, true);

#ifdef EMU

int main() {
    setup();
    signal(SIGINT, interrupt_sig);
    while (true) loop();
}


void interrupt_sig(int signo) {
    REPORT("sys", "interrupt recv", signo);
    change_mode();
}

#endif


void change_mode() {
    p_index++;
    p_index %= P_COUNT;
    assert(p_index > -1);
    assert(p_index < P_COUNT);
    s->setProgram(programs[p_index]);
}


void setup() {
#ifndef EMU
    Serial.begin(9600);
#endif

    Layer *l0 = new Layer(1);
    l0->addLedOnPin(l0p0);
    Layer *l1 = new Layer(2);
    l1->addLedOnPin(l1p0);
    l1->addLedOnPin(l1p1);
    Layer *l2 = new Layer(2);
    l2->addLedOnPin(l2p0);
    l2->addLedOnPin(l2p1);
    Layer *l3 = new Layer(2);
    l3->addLedOnPin(l3p0);
    l3->addLedOnPin(l3p1);
    s->addLayer(l0);
    s->addLayer(l1);
    s->addLayer(l2);
    s->addLayer(l3);
    String program = programs[p_index];
    s->setProgram(program);
    modeButton->setHandler(change_mode);
    modeButton->attachInterrupt(I_MODE_RISING);
}

void loop() {
    s->exec();
    if (loveButton->readState() == HIGH) {
        Serial.println("Spruce made with love from Alexander to Ann\n");
        Serial.println("            ******       ******     ");
        Serial.println("          **********   **********   ");
        Serial.println("        ************* ************* ");
        Serial.println("       *****************************");
        Serial.println("       *****************************");
        Serial.println("       *****************************");
        Serial.println("        *************************** ");
        Serial.println("          ***********************   ");
        Serial.println("            *******************     ");
        Serial.println("              ***************       ");
        Serial.println("                ***********         ");
        Serial.println("                  *******           ");
        Serial.println("                    ***             ");
        Serial.println("                     *              \n");
    }
}
