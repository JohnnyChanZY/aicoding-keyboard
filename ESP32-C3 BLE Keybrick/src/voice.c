#include "voice.h"

VoiceContext voiceCtx = {
    .state = VOICE_IDLE,
    .startTime = 0,
    .bufferLen = 0
};

/**
  * @brief  Initialize voice input module
  * @param  None
  * @retval true if successful, false otherwise
  */
bool VOICE_Init(void) {
    if (!MIC_Init()) {
        return false;
    }

    voiceCtx.state = VOICE_IDLE;
    voiceCtx.startTime = 0;
    voiceCtx.bufferLen = 0;

    return true;
}

/**
  * @brief  Start voice recording
  * @param  None
  * @retval true if successful, false otherwise
  */
bool VOICE_StartRecording(void) {
    if (voiceCtx.state != VOICE_IDLE) {
        return false;
    }

    if (!MIC_Start()) {
        return false;
    }

    voiceCtx.state = VOICE_RECORDING;
    voiceCtx.startTime = millis();
    voiceCtx.bufferLen = 0;

    return true;
}

/**
  * @brief  Stop voice recording and process audio
  * @param  None
  * @retval None
  */
void VOICE_StopRecording(void) {
    if (voiceCtx.state != VOICE_RECORDING) {
        return;
    }

    MIC_Stop();
    voiceCtx.state = VOICE_PROCESSING;
}

/**
  * @brief  Update voice state (called in main loop)
  * @param  None
  * @retval None
  */
void VOICE_Update(void) {
    switch (voiceCtx.state) {
        case VOICE_IDLE:
            // Do nothing
            break;

        case VOICE_RECORDING:
            // Check for maximum duration
            if (millis() - voiceCtx.startTime > VOICE_MAX_DURATION) {
                VOICE_StopRecording();
                return;
            }

            // Read audio data from microphone
            size_t bytesRead = MIC_Read(voiceCtx.audioBuffer + voiceCtx.bufferLen,
                                        sizeof(int16_t) * (VOICE_BUFFER_SIZE - voiceCtx.bufferLen));
            if (bytesRead > 0) {
                voiceCtx.bufferLen += bytesRead / sizeof(int16_t);

                // Buffer full, process and send
                if (voiceCtx.bufferLen >= VOICE_BUFFER_SIZE) {
                    MIC_Stop();
                    voiceCtx.state = VOICE_SENDING;
                }
            }
            break;

        case VOICE_PROCESSING:
            // Process recorded audio (placeholder for voice recognition)
            // This would typically involve sending audio to a recognition service
            voiceCtx.state = VOICE_SENDING;
            break;

        case VOICE_SENDING:
            // Send processed result (placeholder for actual implementation)
            // After sending, return to idle state
            voiceCtx.state = VOICE_IDLE;
            voiceCtx.bufferLen = 0;
            break;
    }
}

/**
  * @brief  Check if voice recording is active
  * @param  None
  * @retval true if recording, false otherwise
  */
bool VOICE_IsRecording(void) {
    return voiceCtx.state == VOICE_RECORDING;
}

/**
  * @brief  Get current voice state
  * @param  None
  * @retval Current VoiceState
  */
VoiceState VOICE_GetState(void) {
    return voiceCtx.state;
}
