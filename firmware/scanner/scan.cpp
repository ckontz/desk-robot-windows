// I2C scanner: prints the address of every device that answers on the OLED's bus.
// Build and flash with `pio run -e scanner -t upload`, then `pio device monitor`.

#include <Arduino.h>
#include <Wire.h>

void setup() {
  Serial.begin(115200);
  delay(2000);        // give the USB serial monitor time to connect
  Wire.begin(5, 6);   // SDA=GPIO5 (D4), SCL=GPIO6 (D5), the same pins as the firmware
}

void loop() {
  int found = 0;
  for (uint8_t addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {   // 0 = a device acknowledged
      Serial.printf("Found device at 0x%02X\n", addr);
      found++;
    }
  }
  if (!found) Serial.println("No I2C devices found: check wiring, power and the pull-ups");
  Serial.println("--- scan done ---");
  delay(3000);
}
