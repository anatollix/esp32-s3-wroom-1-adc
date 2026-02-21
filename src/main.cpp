#include <Arduino.h>

#define ADC_PIN 5
#define ADC_RESOLUTION 12
#define ADC_ATTENUATION ADC_11db
#define ADC_MAX_VALUE ((1 << ADC_RESOLUTION) - 1)
#define ADC_REF_VOLTAGE 3300
 

void setup() {
  Serial.begin(115200);
  delay(3000);

  Serial.println("\n========================================");
  Serial.println("   ESP32-S3 ADC");
  Serial.println("========================================");
  Serial.printf("Board: ESP32-S3-WROOM-1\n");
  Serial.printf("CPU Freq: %d MHz\n", ESP.getCpuFreqMHz());
  Serial.printf("Free Heap: %d bytes\n", ESP.getFreeHeap());
  Serial.println("========================================\n");
  
  analogReadResolution(ADC_RESOLUTION);
  analogSetAttenuation(ADC_ATTENUATION);

  analogReadMilliVolts(ADC_PIN); // Init log before the table header

  Serial.println("+-------+----------+----------+----------+----------+");
  Serial.println("| ADC   | ADC V    | Read V   | Diff     | Error    |");
  Serial.println("+-------+----------+----------+----------+----------+");
  delay(1000);
}

void loop() {
  int adcValue = analogRead(ADC_PIN);
  float adcVoltValue = (float)adcValue * ADC_REF_VOLTAGE / ADC_MAX_VALUE;
  int analogVoltage = analogReadMilliVolts(ADC_PIN);
  float diff = fabsf(analogVoltage - adcVoltValue);
  float errPct = analogVoltage > 0 ? (diff / analogVoltage) * 100.0f : 0.0f;

  Serial.printf( "| %5d | %6.3f V | %6.3f V | %6.3f V | %6.2f %% |\n",
                 adcValue,
                 adcVoltValue / 1000.0f,
                 analogVoltage / 1000.0f,
                 diff / 1000.0f,
                 errPct);
  delay(100);
}
