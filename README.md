# led

ESP32 上跑 LED 闪烁的最小 PlatformIO 工程（Arduino 框架）。

## 硬件

| 项目 | 值 |
|---|---|
| 板子 | 经典 ESP32-D0WD-V3（Espressif ESP32 Dev Module），双核 240MHz |
| Flash | 4MB（`esptool flash_id` 实测：Manufacturer `a1` / Device `4016`） |
| LED 引脚 | **GPIO 4** |
| 下载口 | 板载 USB-UART 桥（macOS 上枚举为 `/dev/cu.usbserial-*`） |

> ⚠️ 经典 ESP32 的 **GPIO 34~39 是输入专用脚**，没有输出驱动能力，不能用来点 LED。
> 可换用 GPIO 2 / 4 / 5 / 12~19 / 21~23 / 25~27 / 32 / 33。

## 接线（外接 LED 时）

```
GPIO4 ──[220Ω~1kΩ]──►│ LED │──► GND
                     阳极  阴极
```

## 行为

- 亮 500ms / 灭 500ms 循环，节奏由 `src/main.cpp` 里的 `BLINK_INTERVAL_MS` 控制。
- 上电先熄灭，再开始闪。
- 串口（115200）打印每次开关的时间戳，便于确认程序在跑。

```cpp
static const uint8_t LED_PIN = 4;               // 目标引脚
static const uint32_t BLINK_INTERVAL_MS = 500;  // 半周期时长(毫秒)
static const bool LED_ACTIVE_HIGH = true;       // 低电平点亮改为 false
```

## 构建 / 烧录 / 看串口

```bash
pio run -e esp32dev                 # 编译
pio run -e esp32dev -t upload       # 编译并烧录
pio device monitor -e esp32dev      # 串口监视器 (115200)
```

## 环境说明

平台 `espressif32@7.1.3` 在 `platformio.ini` 里 **钉住了 framework `4.20017.260907`（Arduino core 2.0.17）**，这是该平台版本官方匹配的组合。原因见配置内注释：registry 上更新的 `4.30312.261001`（core 3.3.12）在本平台下不可用——它的预编译库包要求 GCC 14/15，而本平台为经典 ESP32 指定的是 GCC 8.4。

该 framework 包约 246MB，慢链路上首次安装耗时较长；传输中断会报 `HTTPClientError`，**重试即可**（已下载部分会被复用）。
