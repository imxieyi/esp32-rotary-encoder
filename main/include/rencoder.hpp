#pragma once

#include "driver/gpio.h"
#include "driver/pcnt.h"

class RENCODER {
private:
    pcnt_unit_t unit;
public:
    RENCODER(gpio_num_t a, gpio_num_t b, gpio_num_t ctrl,
             pcnt_unit_t unit);
    void pause();
    void clear();
    void resume();
    int16_t value();
};
