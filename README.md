# AI Coding Keyboard

基于 ESP32-C3 的多功能蓝牙小键盘，支持 5 个自定义按键和语音输入功能。

 Fork 自 [WilliTourt/ESP32-Keyboard-Customized](https://github.com/WilliTourt/ESP32-Keyboard-Customized)，新增麦克风功能。

---

## 功能特性

- [√] 发送单个按键
- [√] 发送组合键
- [-] 发送媒体键
- [√] 倒计时定时器
- [√] 节拍器
- [√] 加载预设配置
- [√] 电池电量监测
- [-] 自动重连
- [√] **语音输入**（新增，通过 I2S 麦克风）

## 硬件组成

| 模块 | 说明 |
|------|------|
| **主控** | ESP32-C3-MINI-1 模组 |
| **按键** | 5 个机械键盘轴体 |
| **显示** | 0.91 英寸 OLED (128×32) |
| **电源** | TP4056 充电模块 + 3.7V 锂电池 |
| **音频** | 蜂鸣器 + INMP441 麦克风（新增） |
| **指示** | 状态 LED |

---

## 引脚定义

### 原有引脚

```
// 按键
#define BTN_1_PIN       2
#define BTN_2_PIN       3
#define BTN_3_PIN       4
#define BTN_4_PIN       5
#define BTN_5_PIN       8

// OLED I2C
#define OLED_SDA        6
#define OLED_SCL        7

// 其他
#define BUZZER_PIN      1       // 蜂鸣器
#define STATUS_LED      10      // 状态指示灯
#define ADC_PIN         A0      // 电池电压检测
```

### 新增麦克风引脚 (INMP441 I2S)

```
#define I2S_SCK         9       // 串行时钟 (BCLK)
#define I2S_WS          0       // 左右声道选择 (LRCLK)
#define I2S_SD          18      // 数据输入 (DOUT)
```

> ⚠️ **注意**：GPIO 0 是启动引脚，使用时需要注意。建议根据实际 PCB 布局调整引脚分配。

---

## 使用方法

### 编译下载

使用 PlatformIO 打开项目文件夹：

```bash
cd "ESP32-C3 BLE Keybrick"
pio run -t upload
```

### 默认按键配置

| 按键 | 功能 |
|------|------|
| Key 1 | Ctrl+C |
| Key 2 | Ctrl+V |
| Key 3 | Ctrl+X |
| Key 4 | 无（长按进入节拍器模式）|
| Key 5 | 无（长按进入定时器设置）|

### 特殊操作

- **长按 Key 4**：进入节拍器模式
- **长按 Key 5**：进入定时器设置
- **同时长按 Key 4 + Key 5**：进入按键配置模式

---

## 语音功能（开发中）

当前已实现：
- I2S 麦克风驱动 (INMP441)
- 音频数据采集
- 录音状态机

待实现：
- 语音识别集成（对接语音识别服务）
- 按键触发语音输入
- OLED 显示录音状态

---

## PCB 改动说明

在原有 PCB 基础上，需要增加：

1. **INMP441 麦克风模块焊盘**
   - 6 个引脚：VCC、GND、SCK、WS、SD、L/R
   
2. **I2S 信号走线**
   - SCK → GPIO 9
   - WS → GPIO 0
   - SD → GPIO 18 (或其他可用 GPIO)

3. **电源**
   - VCC 接 3.3V
   - GND 接地

---

## 硬件物料清单 (BOM)

原有器件请参考原项目 BOM。

新增麦克风模块：

| 器件 | 型号 | 数量 | 参考价格 |
|------|------|------|---------|
| MEMS 麦克风 | INMP441 | 1 | ¥15-20 |
| 或 | MSM261S4030H0 | 1 | ¥5-10 |

---

## 项目结构

```
aicoding-keyboard/
├── README.md
├── BOM_ESP32 Keybrick.xlsx       # 物料清单
├── ESP32-C3 BLE Keyboard v1.2.zip # PCB Gerber 文件
├── ESP32 BLE Keyboard v1.2f shell.stl  # 3D 外壳
├── ESP32 BLE Keyboard v1.2f cover.stl  # 外壳盖子
└── ESP32-C3 BLE Keybrick/        # 固件源码
    ├── platformio.ini
    ├── include/
    │   ├── def.h      # 引脚定义
    │   ├── mic.h      # 麦克风驱动 (新增)
    │   ├── voice.h    # 语音模块 (新增)
    │   └── ...
    ├── src/
    │   ├── main.cpp   # 主程序
    │   ├── mic.c      # 麦克风驱动 (新增)
    │   ├── voice.c    # 语音模块 (新增)
    │   └── ...
    └── lib/
        └── hid2ble/   # 蓝牙 HID 库
```

---

## 致谢

- 原项目作者 [WilliTourt](https://github.com/WilliTourt)
- 蓝牙 HID 库 [Hid2Ble](https://github.com/BearLaboratory/Hid2Ble)

---

## 开源协议

GPL 3.0
