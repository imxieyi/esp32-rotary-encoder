# ESP32 Rotary Encoder driver for esp-idf
Both phase A and phase B are required. On 25GA20E260 motor the counter will increase by 1040 in each rotation.

It uses gpio interrupt instead of [PCNT](https://esp-idf.readthedocs.io/en/latest/api-reference/peripherals/pcnt.html). So you must call **rencoder_init()** before creating any RENCODER. If you prefer PCNT, please refer to branch [pcnt](https://github.com/imxieyi/esp32-rotary-encoder/tree/pcnt).
