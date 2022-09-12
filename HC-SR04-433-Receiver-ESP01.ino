#include <Wire.h>
#include <RH_ASK.h>

bool constexpr SerialEnabled = true;

RH_ASK driver(2000, 4, 12);
// RH_ASK driver(2000, 11, 12);

void onRequest();
void buffAdd(uint8_t c);

void setup() {
  if (SerialEnabled) Serial.begin(115200);
  Wire.begin(0x11);
  Wire.onRequest(onRequest);
  if (!driver.init()) {
    if (SerialEnabled) Serial.println("drv fail");
  }

  // if (SerialEnabled) Serial.print("driver max: ");
  // if (SerialEnabled) Serial.println(driver.maxMessageLength());
  if (SerialEnabled) Serial.println("hc began");
}

uint8_t data[64];
uint8_t dataLength;

void loop() {
  if (driver.available()) {
    dataLength = sizeof(data);
    if (!driver.recv(data, &dataLength)) {
      return;
    }
    if (dataLength == 0 || dataLength == 0xFF) {
      return;
    }

    for (uint8_t i = 0; i < dataLength; ++i) {
      if (SerialEnabled) {
        if (data[i] < 0x10) Serial.print('0');
        Serial.print((int)data[i], HEX);
      }
      buffAdd(data[i]);
    }
    if (SerialEnabled) Serial.println();
  }
}
