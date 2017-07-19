#pragma once

#include "driver/gpio.h"

void rencoder_init();

class RENCODER {
private:
    gpio_num_t a, b;
    int32_t count;
    bool direction;
    bool working;
public:
    RENCODER(gpio_num_t a, gpio_num_t b);
    ~RENCODER();
    void interrupt(gpio_num_t gpio);
    void pause();
    void clear();
    void resume();
    bool getdirection();
    int32_t value();
};
