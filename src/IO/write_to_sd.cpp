#include <SD.h>
#include <SPI.h>

#include <array>

File data;

bool SD_begin() {
  SD.begin(CS_PIN);
  data = SD.open("data", FILE_WRITE);
}

template <typename T>
void write_to_sd(T obj) {

  data.write(reinterpret_cast<unsigned char*>(&obj), sizeof(obj);

}
