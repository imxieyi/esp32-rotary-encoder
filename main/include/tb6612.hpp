#pragma once

#include "driver/gpio.h"
#include "driver/mcpwm.h"
#include "soc/mcpwm_reg.h"
#include "soc/mcpwm_struct.h"

#define MOTOR0  MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM0A, MCPWM_OPR_A
#define MOTOR1  MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM1A, MCPWM_OPR_A
#define MOTOR2  MCPWM_UNIT_0, MCPWM_TIMER_2, MCPWM2A, MCPWM_OPR_A
#define MOTOR3  MCPWM_UNIT_1, MCPWM_TIMER_0, MCPWM0A, MCPWM_OPR_A
#define MOTOR4  MCPWM_UNIT_1, MCPWM_TIMER_1, MCPWM1A, MCPWM_OPR_A
#define MOTOR5  MCPWM_UNIT_1, MCPWM_TIMER_2, MCPWM2A, MCPWM_OPR_A
#define MOTOR6  MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM0B, MCPWM_OPR_B
#define MOTOR7  MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM1B, MCPWM_OPR_B
#define MOTOR8  MCPWM_UNIT_0, MCPWM_TIMER_2, MCPWM2B, MCPWM_OPR_B
#define MOTOR9  MCPWM_UNIT_1, MCPWM_TIMER_0, MCPWM0B, MCPWM_OPR_B
#define MOTOR10 MCPWM_UNIT_1, MCPWM_TIMER_1, MCPWM1B, MCPWM_OPR_B
#define MOTOR11 MCPWM_UNIT_1, MCPWM_TIMER_2, MCPWM2B, MCPWM_OPR_B

class MOTOR {
private:
    // 0 - Stop
    // 1 - Run
    //gpio_num_t stby;
    // A1  0  0 1   1
    // A2  0  1 0   1
    //   stop + - brake
    gpio_num_t a1, a2;
    // ~100 kHz
    // GPIO port for pwm out
    gpio_num_t pwmport;
    // Unit number of MCPWM (Total 2)
    mcpwm_unit_t unit;
    // Timer of MCPWM unit (Total 3)
    mcpwm_timer_t timer;
    // IO signal of MCPWM unit (Total 6)
    mcpwm_io_signals_t iosig;
    // Operator of MCPWM unit (Total 2)
    mcpwm_operator_t op;
public:
    MOTOR(gpio_num_t a1, gpio_num_t a2, gpio_num_t pwm,
          // The following 4 parameters can be simply passed using macro MOTOR0~5
          mcpwm_unit_t unit, mcpwm_timer_t timer, mcpwm_io_signals_t iosig, mcpwm_operator_t op);
    ~MOTOR();
    // Speed 0~100
    void setspeed(float speed);
    // direction: The direction of motor
    void start(bool direction);
    // The motor will slowly stop because of inertia
    void stop();
    // The motor will immediately stop
    void brake();
};
