#include "mic.h"

MicState micState = {
    .isInitialized = false,
    .isRecording = false,
    .sampleCount = 0
};

/**
  * @brief  Initialize I2S microphone (INMP441)
  * @param  None
  * @retval true if successful, false otherwise
  */
bool MIC_Init(void) {
    if (micState.isInitialized) {
        return true;
    }

    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
        .sample_rate = I2S_SAMPLE_RATE,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
        .communication_format = I2S_COMM_FORMAT_STAND_I2S,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = I2S_DMA_BUF_COUNT,
        .dma_buf_len = I2S_DMA_BUF_LEN,
        .use_apll = false,
        .tx_desc_auto_clear = false,
        .fixed_mclk = 0
    };

    i2s_pin_config_t pin_config = {
        .bck_io_num = I2S_SCK,
        .ws_io_num = I2S_WS,
        .data_out_num = I2S_PIN_NO_CHANGE,
        .data_in_num = I2S_SD
    };

    esp_err_t err = i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
    if (err != ESP_OK) {
        return false;
    }

    err = i2s_set_pin(I2S_PORT, &pin_config);
    if (err != ESP_OK) {
        i2s_driver_uninstall(I2S_PORT);
        return false;
    }

    micState.isInitialized = true;
    micState.isRecording = false;
    micState.sampleCount = 0;

    return true;
}

/**
  * @brief  Start recording audio from microphone
  * @param  None
  * @retval true if successful, false otherwise
  */
bool MIC_Start(void) {
    if (!micState.isInitialized) {
        return false;
    }

    if (micState.isRecording) {
        return true;
    }

    i2s_zero_dma_buffer(I2S_PORT);
    micState.isRecording = true;
    micState.sampleCount = 0;

    return true;
}

/**
  * @brief  Stop recording audio from microphone
  * @param  None
  * @retval None
  */
void MIC_Stop(void) {
    if (!micState.isInitialized || !micState.isRecording) {
        return;
    }

    micState.isRecording = false;
}

/**
  * @brief  Read audio data from microphone
  * @param  buffer: Pointer to buffer for audio data
  * @param  bytesToRead: Number of bytes to read
  * @retval Number of bytes actually read
  */
size_t MIC_Read(int16_t* buffer, size_t bytesToRead) {
    if (!micState.isInitialized || !micState.isRecording) {
        return 0;
    }

    size_t bytesRead = 0;
    i2s_read(I2S_PORT, (void*)buffer, bytesToRead, &bytesRead, portMAX_DELAY);

    if (bytesRead > 0) {
        micState.sampleCount += bytesRead / sizeof(int16_t);

        // INMP441 outputs 24-bit data in 32-bit frame, shift right by 16 bits
        // to get the most significant 16 bits
        int samples = bytesRead / sizeof(int16_t);
        for (int i = 0; i < samples; i++) {
            buffer[i] = buffer[i] >> 1;  // Adjust gain/scaling as needed
        }
    }

    return bytesRead;
}

/**
  * @brief  Deinitialize I2S microphone
  * @param  None
  * @retval None
  */
void MIC_Deinit(void) {
    if (!micState.isInitialized) {
        return;
    }

    micState.isRecording = false;
    i2s_driver_uninstall(I2S_PORT);
    micState.isInitialized = false;
}
