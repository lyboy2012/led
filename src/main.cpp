/*
 * LED 闪烁 — 经典 ESP32-D0WD-V3 (Espressif ESP32 Dev Module, 双核 240MHz)
 *
 * 目标引脚: GPIO 4
 * 闪烁节奏: 亮 500ms / 灭 500ms (可通过 BLINK_INTERVAL_MS 调整)
 *
 * ⚠️ 经典 ESP32 的 GPIO 34~39 是「输入专用」脚，没有输出驱动能力，
 *    不能用来点 LED；想换脚请选 GPIO 2/4/5/12~19/21~23/25~27/32/33。
 *
 * 接线(用外接 LED 时):
 *    GPIO4 --[220Ω~1kΩ]--> LED 阳极(长脚) ; LED 阴极(短脚) --> GND
 *
 * 说明: 若换成板载 LED，多数开发板串在 GPIO2 上且多为「低电平点亮」，
 *       若发现亮灭相反，把 LED_ACTIVE_HIGH 改成 false 即可。
 */

#include <Arduino.h>

// ======== 可配置项 ========
static const uint8_t LED_PIN = 4;               // 目标引脚: GPIO 4
static const uint32_t BLINK_INTERVAL_MS = 500;  // 半周期时长(毫秒)
static const bool LED_ACTIVE_HIGH = true;       // 高电平点亮; 低电平点亮改为 false

// 根据有效电平把 亮/灭 换算成实际输出电平
static inline uint8_t ledLevel(bool on) {
  if (LED_ACTIVE_HIGH) {
    return on ? HIGH : LOW;
  }
  return on ? LOW : HIGH;
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, ledLevel(false));  // 上电先熄灭，避免闪一下

  delay(200);
  Serial.println();
  Serial.println("=================================");
  Serial.println("ESP32-D0WD-V3 (ESP32 Dev Module)");
  Serial.printf("LED blink on GPIO %u, interval %lu ms\n",
                (unsigned)LED_PIN, (unsigned long)BLINK_INTERVAL_MS);
  Serial.println("=================================");
}

void loop() {
  digitalWrite(LED_PIN, ledLevel(true));
  Serial.printf("[%8lu ms] GPIO%u = ON\n", (unsigned long)millis(),
                (unsigned)LED_PIN);
  delay(BLINK_INTERVAL_MS);

  digitalWrite(LED_PIN, ledLevel(false));
  Serial.printf("[%8lu ms] GPIO%u = OFF\n", (unsigned long)millis(),
                (unsigned)LED_PIN);
  delay(BLINK_INTERVAL_MS);
}
