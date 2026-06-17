#include <fstream>

namespace git_index {
  
  struct header_t {
    char type_id[4] {0};
    unsigned int version {0};
    unsigned int num_entries {0};
  };

  inline header_t read_header(std::ifstream& file) {
    header_t to_return {};
    file.read(to_return.type_id, 4);
    file.read(reinterpret_cast<char*>(&to_return.version), 4);
    file.read(reinterpret_cast<char*>(&to_return.num_entries), 4);
    
    return to_return;
  }

};
