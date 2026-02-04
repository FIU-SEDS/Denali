#include <serial.h>
#include <vector>
#include <stdint.h>

template <typename T>
std::vector<uint8_t> get_serialized(T t) {
  uint8_t *arr = reinterpret_cast<uint8_t*>(&t);
  std::vector<uint8_t> serialized(sizeof(t));
  
  for(std::size_t i = 0; i < sizeof(t); i++)
    serialized[i] = arr[i];

  return serialized;
}
