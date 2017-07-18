#include "rencoder.hpp"

RENCODER::RENCODER(gpio_num_t a, gpio_num_t b, gpio_num_t ctrl,
                   pcnt_unit_t unit) {
    pcnt_config_t configa;
    configa.pulse_gpio_num = a;
    configa.ctrl_gpio_num = ctrl;
    configa.channel = PCNT_CHANNEL_0;
    configa.unit = unit;
    configa.pos_mode = PCNT_COUNT_INC;
    configa.neg_mode = PCNT_COUNT_INC;
    configa.lctrl_mode = PCNT_MODE_KEEP;
    configa.hctrl_mode = PCNT_MODE_KEEP;
    configa.counter_h_lim = INT16_MAX;
    configa.counter_l_lim = INT16_MIN;
    pcnt_config_t configb;
    configb.pulse_gpio_num = b;
    configb.ctrl_gpio_num = ctrl;
    configb.channel = PCNT_CHANNEL_1;
    configb.unit = unit;
    configb.pos_mode = PCNT_COUNT_INC;
    configb.neg_mode = PCNT_COUNT_INC;
    configb.lctrl_mode = PCNT_MODE_KEEP;
    configb.hctrl_mode = PCNT_MODE_KEEP;
    configb.counter_h_lim = INT16_MAX;
    configb.counter_l_lim = INT16_MIN;
    pcnt_unit_config(&configa);
    pcnt_unit_config(&configb);
    pcnt_filter_disable(unit);
    this -> unit = unit;
}

void RENCODER::pause() {
    pcnt_counter_pause(unit);
}

void RENCODER::clear() {
    pcnt_counter_clear(unit);
}

void RENCODER::resume() {
    pcnt_counter_resume(unit);
}

int16_t RENCODER::value() {
    int16_t count;
    pcnt_get_counter_value(unit, &count);
    return count;
}
