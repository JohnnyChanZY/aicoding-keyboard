#ifndef __DEF_H__
#define __DEF_H__

#include <Arduino.h>

// Pin definitions
#define ADC_PIN         A0
#define BUZZER_PIN      1
#define BTN_1_PIN       2
#define BTN_2_PIN       3
#define BTN_3_PIN       4
#define BTN_4_PIN       5
#define OLED_SDA        6
#define OLED_SCL        7
#define BTN_5_PIN       8
#define STATUS_LED      10

// I2S Microphone (INMP441) Pin definitions
#define I2S_SCK         9       // Serial Clock (BCLK)
#define I2S_WS          0       // Word Select (LRCLK)
#define I2S_SD          18      // Serial Data (DOUT)

// I2S configuration
#define I2S_PORT        I2S_NUM_0
#define I2S_SAMPLE_RATE 16000
#define I2S_BITS_PER_SAMPLE 16
#define I2S_DMA_BUF_COUNT 8
#define I2S_DMA_BUF_LEN   512

#endif