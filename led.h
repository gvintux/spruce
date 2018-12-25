#ifndef LED_H
#define LED_H

typedef enum {
    LC_UNKNOW = '?', LC_ON = 'H', LC_OFF = 'L', LC_TOGGLE = 'T', LC_DELAY = 'D'
} LED_CMD;

class LED {
public:
    LED(int pin);

    ~LED();

    void on();

    void off();

    int toggle();

    int getPin();

    int getState();

private:
    int pin;
    int state;
};

#endif


