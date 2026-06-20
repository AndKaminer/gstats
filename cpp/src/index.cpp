#include <iostream>
#include <string_view>

#include "index.hpp"

namespace git_index {

index_data_t read_index_file(fs::path indexpath) {
  std::ifstream file(indexpath, std::ios::binary);

  header_t header {read_header(file)};

  index_data_t to_return {};
  to_return.version = header.version;
  to_return.num_entries = header.num_entries;

  std::cout << std::string_view{header.type_id, 4} << std::endl << to_return.version << std::endl << to_return.num_entries << std::endl;

  for (int entry_num {0}; entry_num < to_return.num_entries; ++entry_num) {
    index_entry_t entry {};

    file.ignore(9 * sizeof(std::uint32_t)); // read through things we don't care about
    entry.file_size = util::read_big_endian_number32(file);
    file.ignore(20); // read the sha
    
    uint16_t flags {util::read_big_endian_number16(file)};
    uint16_t name_length_mask {0b0000'1111'1111'1111};
    uint16_t name_length {static_cast<uint16_t>(flags & name_length_mask)};

    std::string file_name_s;
    file_name_s.reserve(name_length);
    file.read(file_name_s.data(), name_length);
    entry.path = static_cast<fs::path>(file_name_s);

    to_return.entries.push_back(entry);
  }
  
  return to_return;
}

}
