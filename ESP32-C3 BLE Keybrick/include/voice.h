#ifndef __VOICE_H__
#define __VOICE_H__

#include <Arduino.h>
#include "mic.h"

// Voice recording buffer size
#define VOICE_BUFFER_SIZE   1024
#define VOICE_MAX_DURATION  5000    // Maximum recording duration in ms

// Voice state
typedef enum {
    VOICE_IDLE,
    VOICE_RECORDING,
    VOICE_PROCESSING,
    VOICE_SENDING
} VoiceState;

typedef struct {
    VoiceState state;
    uint32_t startTime;
    int16_t audioBuffer[VOICE_BUFFER_SIZE];
    size_t bufferLen;
} VoiceContext;

extern VoiceContext voiceCtx;

/**
  * @brief  Initialize voice input module
  * @param  None
  * @retval true if successful, false otherwise
  */
bool VOICE_Init(void);

/**
  * @brief  Start voice recording
  * @param  None
  * @retval true if successful, false otherwise
  */
bool VOICE_StartRecording(void);

/**
  * @brief  Stop voice recording and process audio
  * @param  None
  * @retval None
  */
void VOICE_StopRecording(void);

/**
  * @brief  Update voice state (called in main loop)
  * @param  None
  * @retval None
  */
void VOICE_Update(void);

/**
  * @brief  Check if voice recording is active
  * @param  None
  * @retval true if recording, false otherwise
  */
bool VOICE_IsRecording(void);

/**
  * @brief  Get current voice state
  * @param  None
  * @retval Current VoiceState
  */
VoiceState VOICE_GetState(void);

#endif