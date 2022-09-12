#include <Wire.h>

struct Buf {
    uint8_t data[64];
    uint8_t head = 0;
    uint8_t tail = 0;
} buf;

void buffAdd(uint8_t c) {
  buf.data[buf.tail++ % sizeof(buf.data)] = c;
  if (buf.tail % sizeof(buf.data) == buf.head % sizeof(buf.data)) {
    buf.head++;
  }
}

void buffToWire() {
  while (buf.tail % sizeof(buf.data) != buf.head % sizeof(buf.data)) {
    Wire.write(buf.data[buf.head++ % sizeof(buf.data)]);
  }
}

void onRequest() {
  buffToWire();
}
