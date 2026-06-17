#include <cstdint>
#include <fstream>

namespace util {

inline uint32_t swap_endian32(uint32_t val) {
  return ((val & 0xFF000000) >> 24) |
    ((val & 0x00FF0000) >> 8)  |
    ((val & 0x0000FF00) << 8)  |
    ((val & 0x000000FF) << 24);
}

inline uint32_t read_big_endian_number(std::ifstream& file) {
  uint32_t to_return {0};
  file.read(
    reinterpret_cast<char*>(&to_return),
    sizeof(to_return)
  );

  if constexpr (std::endian::native == std::endian::little) {
    to_return = swap_endian32(to_return);
  }
  return to_return;
}

};
