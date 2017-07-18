#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "tb6612.hpp"
#include "rencoder.hpp"

static void motor_task(void *pvParameters) {
    MOTOR m(GPIO_NUM_33, GPIO_NUM_26, GPIO_NUM_27, MOTOR0);
    ESP_LOGI("motor", "set speed to 50%%");
    m.setspeed(50);
    m.start(true);
    vTaskDelay(5000/portTICK_RATE_MS);
    ESP_LOGI("motor", "stop");
    m.stop();
    vTaskDelay(5000/portTICK_RATE_MS);
    ESP_LOGI("motor", "reverse direction");
    m.start(false);
    vTaskDelay(5000/portTICK_RATE_MS);
    ESP_LOGI("motor", "brake");
    m.brake();
    vTaskDelete(0);
}

static void counter_task(void *pvParameters) {
    RENCODER enc(GPIO_NUM_16, GPIO_NUM_17, GPIO_NUM_18, PCNT_UNIT_0);
    enc.pause();
    enc.clear();
    enc.resume();
    while(1) {
        ESP_LOGI("counter", "%d", enc.value());
        enc.clear();
        vTaskDelay(1000/portTICK_RATE_MS);
    }
}

extern "C" void app_main()
{
    xTaskCreatePinnedToCore(&motor_task,"motor_task",2048,NULL,5,NULL,0);
    xTaskCreatePinnedToCore(&counter_task,"counter_task",2048,NULL,5,NULL,1);
}