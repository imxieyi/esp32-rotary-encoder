#include "tb6612.hpp"

MOTOR::MOTOR(gpio_num_t a1, gpio_num_t a2, gpio_num_t pwm,
             mcpwm_unit_t unit, mcpwm_timer_t timer, mcpwm_io_signals_t iosig, mcpwm_operator_t op) {
    this -> a1 = a1;
    this -> a2 = a2;
    this -> pwmport = pwm;
    this -> unit = unit;
    this -> timer = timer;
    this -> iosig = iosig;
    this -> op = op;
    gpio_set_direction(a1, GPIO_MODE_OUTPUT);
    gpio_set_direction(a2, GPIO_MODE_OUTPUT);
    gpio_set_level(a1, 0);
    gpio_set_level(a2, 1);
    mcpwm_gpio_init(unit, iosig, pwm);
    mcpwm_config_t config;
    config.frequency = 100000;
    config.cmpr_a = 0;
    config.cmpr_b = 0;
    config.counter_mode = MCPWM_UP_COUNTER;
    config.duty_mode = MCPWM_DUTY_MODE_0;
    mcpwm_init(unit, timer, &config);
}

MOTOR::~MOTOR() {
    gpio_set_level(a1, 0);
    gpio_set_level(a2, 0);
    mcpwm_stop(unit, timer);
}

void MOTOR::setspeed(float speed) {
    mcpwm_set_duty(unit, timer, op, speed);
}

void MOTOR::start(bool direction) {
    if(direction) {
        gpio_set_level(a1, 0);
        gpio_set_level(a2, 1);
    } else {
        gpio_set_level(a1, 1);
        gpio_set_level(a2, 0);
    }
}

void MOTOR::stop() {
    gpio_set_level(a1, 0);
    gpio_set_level(a2, 0);
}

void MOTOR::brake() {
    gpio_set_level(a1, 1);
    gpio_set_level(a2, 1);
}
