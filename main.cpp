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

static void show_love();

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
const int l0p0 = 10;
const int l1p0 = 14;
const int l1p1 = 15;
const int l2p0 = 6;
const int l2p1 = 16;
const int l3p0 = 0;
const int l3p1 = 1;
const int l3p2 = 4;
const int l3p3 = 5;

static const String P0 = "H3:0D100H3:1D100H3:2D100H3:3D100H2:0D200H2:1D200H1:0D200H1:1D200H0D400L0L1L2L3D400";
static const String P1 = "T3D400T2D400T1D400T0D400";
static const String P2 = "T3:1D100T3:0D100T2:0D100T1:0D100T0D100T1:1D100T2:1D100T3:3D100T3:2D100";
static const String P3 = "H3:0D100H3:1D100H3:2D100H3:3D100H2:1D200H2:0D200H1:0D200H1:1D200H0D400L0L1L2L3D400";
static const String P4 = "T3T2T1T0D1000";
static const String P5 = "T3:0T3:1T2:0T1:0T0D200T3:0T3:1T2:0T1:0T0D200T1:1T2:1T3:2T3:3T0D200T1:1T2:1T3:2T3:3T0D200";
static const String P6 = "H3H2H1H0";
static const String programs[] = {P0, P1, P2, P3, P4, P5, P6};
static const int P_COUNT = 7;
volatile static int p_index = 0;
volatile static int prev_p_index = -1;
volatile static bool need_show_love = false;


static const int MODE_PIN = 2;
static const int LOVE_PIN = 3;

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
    show_love();
}

#endif


void change_mode() {
    if (modeButton->readState() == HIGH) {
        prev_p_index = p_index++;
        p_index %= P_COUNT;
        assert(p_index > -1);
        assert(p_index < P_COUNT);
    }
}


void love_handler() {
    if (loveButton->readState() == HIGH) need_show_love = true;
}

void show_love() {
#ifndef EMU
    if (Serial) {
#endif
    Serial.flush();
    Serial.println("Spruce made with love from Alexander to Ann\n");
    Serial.println("                ,d88b.d88b,");
    Serial.println("                88888888888");
    Serial.println("                `Y8888888Y'");
    Serial.println("                  `Y888Y'");
    Serial.println("                    `Y'\n");
    Serial.flush();
#ifndef EMU

    }
#endif
}

void setup() {
    Serial.begin(57600);
    Layer *l0 = new Layer(1);
    l0->addLedOnPin(l0p0);
    Layer *l1 = new Layer(2);
    l1->addLedOnPin(l1p0);
    l1->addLedOnPin(l1p1);
    Layer *l2 = new Layer(2);
    l2->addLedOnPin(l2p0);
    l2->addLedOnPin(l2p1);
    Layer *l3 = new Layer(4);
    l3->addLedOnPin(l3p0);
    l3->addLedOnPin(l3p1);
    l3->addLedOnPin(l3p2);
    l3->addLedOnPin(l3p3);
    s->addLayer(l0);
    s->addLayer(l1);
    s->addLayer(l2);
    s->addLayer(l3);
    modeButton->setHandler(change_mode);
    modeButton->attachInterrupt(I_MODE_RISING);
    loveButton->setHandler(love_handler);
    loveButton->attachInterrupt(I_MODE_RISING);

}

void loop() {
    if (prev_p_index != p_index) {
        s->setProgram(P_RESET);
        s->exec();
        s->setProgram(programs[p_index]);
        prev_p_index = p_index;
#ifndef EMU
        if (Serial) {
#endif
        Serial.flush();
        Serial.print("p_index = ");
        Serial.println(p_index);
        Serial.flush();
#ifndef EMU
        }
#endif
    }
    if (need_show_love) {
        show_love();
        need_show_love = false;
    }
    s->exec();
}
