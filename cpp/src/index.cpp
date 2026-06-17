#include <iostream>
#include <string_view>

#include "index.hpp"


git_index::index_data_t git_index::read_index_file(fs::path indexpath) {
  std::ifstream file(indexpath, std::ios::binary);

  git_index::header_t header {git_index::read_header(file)};
  
  std::cout << std::string_view(header.type_id, 4) << std::endl << header.version << std::endl << header.num_entries << std::endl;
  
  return git_index::index_data_t {};
}
