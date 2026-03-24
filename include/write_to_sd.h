#ifndef WRITE_SD
#define WRITE_SD

#include <SPI.h>
#include <SD.h>

#include "serial.h"

constexpr int CS_PIN = 0;

// global SD card object

bool SD_begin();

template <typename T>
void write_to_sd(T t) {
  auto bytes = get_serialized(t);
  bytes.insert(t.begin(), t.id);
}

template <typename T>
void write_to_sd(T obj) {

  data.write(reinterpret_cast<unsigned char*>(&obj), sizeof(obj);

}

#endif // WRITE_SD
