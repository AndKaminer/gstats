#include <fstream>
#include <cstdint>
#include <vector>
#include <filesystem>

#include "util.hpp"

namespace git_index {

namespace fs = std::filesystem;

struct header_t {
  std::uint32_t version {0};
  std::uint32_t num_entries {0};
  char type_id[4] {0};

};

struct index_entry_t {
  char path;
  char obj_type;
  int file_size;
  char checksum;
};

struct index_data_t {
  std::vector<index_entry_t> entries {};
  std::uint32_t version {0};
  std::uint32_t num_entries {0};
  char* extension_data {nullptr};
  char checksum[20] {0};
    };

inline header_t read_header(std::ifstream& file) {
  header_t to_return {};
  file.read(to_return.type_id, 4);
  to_return.version = util::read_big_endian_number(file);
  to_return.num_entries = util::read_big_endian_number(file);
  
  return to_return;
}

index_data_t read_index_file(fs::path indexpath);

};
