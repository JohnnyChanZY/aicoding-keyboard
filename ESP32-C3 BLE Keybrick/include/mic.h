#ifndef __MIC_H__
#define __MIC_H__

#include <Arduino.h>
#include <driver/i2s.h>
#include "def.h"

// Microphone state
typedef struct {
    bool isInitialized;
    bool isRecording;
    uint32_t sampleCount;
} MicState;

extern MicState micState;

/**
  * @brief  Initialize I2S microphone (INMP441)
  * @param  None
  * @retval true if successful, false otherwise
  */
bool MIC_Init(void);

/**
  * @brief  Start recording audio from microphone
  * @param  None
  * @retval true if successful, false otherwise
  */
bool MIC_Start(void);

/**
  * @brief  Stop recording audio from microphone
  * @param  None
  * @retval None
  */
void MIC_Stop(void);

/**
  * @brief  Read audio data from microphone
  * @param  buffer: Pointer to buffer for audio data
  * @param  bytesToRead: Number of bytes to read
  * @retval Number of bytes actually read
  */
size_t MIC_Read(int16_t* buffer, size_t bytesToRead);

/**
  * @brief  Deinitialize I2S microphone
  * @param  None
  * @retval None
  */
void MIC_Deinit(void);

#endif
