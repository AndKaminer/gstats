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

  for (auto entry_num {0}; entry_num < to_return.num_entries; ++entry_num) {
    index_entry_t entry {};
    long starting_offset {file.tellg()};

    file.ignore(2 * sizeof(std::uint32_t)); // read through things we don't care about
    entry.obj_type = util::read_big_endian_number32(file) >> 12;
    file.ignore(6 * sizeof(std::uint32_t)); // read through things we don't care about
    entry.file_size = util::read_big_endian_number32(file);
    file.ignore(20); // read the sha
    
    uint16_t flags {util::read_big_endian_number16(file)};
    uint16_t name_length_mask {0b0000'1111'1111'1111};
    uint16_t name_length {static_cast<uint16_t>(flags & name_length_mask)};

    std::string file_name_s;
    file_name_s.resize(name_length);
    file.read(file_name_s.data(), name_length);
    entry.path = static_cast<fs::path>(file_name_s);

    to_return.entries.push_back(entry);

    long entry_size {file.tellg() - starting_offset};
    long padding_needed {8 - entry_size % 8};
    file.ignore(padding_needed);

    std::cout << entry.path << " " << entry.file_size << " " << entry.obj_type << std::endl;
  }
  
  return to_return;
}

}
