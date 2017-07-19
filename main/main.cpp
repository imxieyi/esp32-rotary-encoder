#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"

#include "driver/uart.h"

#include "tb6612.hpp"
#include "rencoder.hpp"

MOTOR *m;

static void motor_task(void *pvParameters) {
    MOTOR m(GPIO_NUM_32, GPIO_NUM_26, GPIO_NUM_27, MOTOR0);
    m.setspeed(50);
    vTaskDelay(5000/portTICK_RATE_MS);
    m.setspeed(-50);
    vTaskDelay(5000/portTICK_RATE_MS);
    m.brake();
    vTaskDelete(0);
}

static void counter_task(void *pvParameters) {
    rencoder_init();
    RENCODER enc(GPIO_NUM_16, GPIO_NUM_17);
    enc.pause();
    enc.clear();
    enc.resume();
    while(1) {
        vTaskDelay(50/portTICK_RATE_MS);
        printf("%d\n", enc.value());
        //printf("%.3f\n", (float)enc.value()/1040/0.05);
        enc.clear();
    }
}

static void uart_task(void *pvParameters) {
    m = new MOTOR(GPIO_NUM_32, GPIO_NUM_26, GPIO_NUM_27, MOTOR0);

    uart_driver_install(UART_NUM_0, 256, 0, 0, NULL, 0);
    uint8_t *data = (uint8_t*) malloc(128);
    int len;
    while(1) {
        len = uart_read_bytes(UART_NUM_0, data, 128, 20/portTICK_RATE_MS);
        //uart_write_bytes(UART_NUM_0, (const char*)data, len);
        if(len > 0) {
            data[len] = 0;
            //printf("speed: %d\n", atoi((const char*)data));
            m -> setspeed((float)atoi((const char*)data));
            m -> start(true);
        }
    }
}

extern "C" void app_main()
{
    xTaskCreatePinnedToCore(&motor_task,"motor_task",2048,NULL,5,NULL,0);
    xTaskCreatePinnedToCore(&counter_task,"counter_task",2048,NULL,5,NULL,1);
    //xTaskCreatePinnedToCore(&uart_task,"uart_task",2048,NULL,5,NULL,1);
}