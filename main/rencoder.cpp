#include "rencoder.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

static RENCODER *gpio2enc[48];
static xQueueHandle gpio_evt_queue = NULL;

static void IRAM_ATTR gpio_isr_handler(void* arg) {
    gpio_num_t gpio_num = (gpio_num_t)(int) arg;
    if(gpio2enc[gpio_num] != NULL)
        gpio2enc[gpio_num] -> interrupt(gpio_num);
}

void rencoder_init() {
    gpio_evt_queue = xQueueCreate(16, sizeof(uint32_t));
    gpio_install_isr_service(0);
}

RENCODER::RENCODER(gpio_num_t a, gpio_num_t b) {
    this -> a = a;
    this -> b = b;
    gpio2enc[a] = this;
    gpio2enc[b] = this;
    count = 0;
    working = true;
    gpio_config_t conf;
    conf.intr_type = GPIO_INTR_ANYEDGE;
    conf.mode = GPIO_MODE_INPUT;
    conf.pin_bit_mask = (1 << a) | (1 << b);
    conf.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio_config(&conf);

    gpio_isr_handler_add(a, gpio_isr_handler, (void*)a);
    gpio_isr_handler_add(b, gpio_isr_handler, (void*)b);
}

RENCODER::~RENCODER() {
    gpio_isr_handler_remove(a);
    gpio_isr_handler_remove(b);
    gpio2enc[a] = NULL;
    gpio2enc[b] = NULL;
}

void RENCODER::interrupt(gpio_num_t gpio) {
    if(working) {
        if(gpio == a && gpio_get_level(a))
            direction = gpio_get_level(b);
        if(direction) {
            count++;
        } else {
            count--;
        }
    }
}

void RENCODER::pause() {
    working = false;
}

void RENCODER::clear() {
    count = 0;
}

void RENCODER::resume() {
    working = true;
}

int32_t RENCODER::value() {
    return count;
}

bool RENCODER::getdirection() {
    return direction;
}
