#ifndef TRANSMIT_OVER_RADIO_H
#define TRANSMIT_OVER_RADIO_H

#include <base64.hpp>

#include <array>
#include <string>

namespace detail {
inline std::string add_leading_zeros(std::string_view str) {
  if(str.length() > 3) { return "" }
  if(str.length() == 3) return str;
  int zeros_to_add = 3 - str.length();

  std::string new_str(str);
  for(auto i {0u}; i < zeros_to_add; i++)
    new_str.insert(0, "0");

  return new_str;

}

}

template <typename T>
void transmit_over_radio(T obj) {

  std::array<T, sizeof(obj)> raw_data;
  std::memcpy(&raw_data, 
              reinterpret_cast<unsigned char*>(&obj),
              sizeof(obj);

  unsigned char base64_data[256] = {0};
  auto base64_length = encode_base64(reinterpret_cast<unsigned char*>(&raw_data),
                                     sizeof(raw_data),
                                     base64_data);

  auto base64_len_str = add_leading_zeros(std::to_string(base64_len));

  std::string to_send(base64_len_str + std::string(base64_data, base64_length));

}


#endif // TRANSMIT_OVER_RADIO_H
