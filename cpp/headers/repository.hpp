#include <filesystem>
#include <stdexcept>
#include <sstream>

namespace repository {

namespace fs = std::filesystem;

inline fs::path get_repository_base(const fs::path& provided_path) {
  fs::path final_path {provided_path};

  if (!fs::is_directory(final_path)) {
    final_path = final_path.parent_path();
  }

  do {
    if (fs::exists((final_path / ".git"))) {
      return final_path;
    }

    final_path = final_path.parent_path();
  }
  while (final_path != final_path.parent_path());
  
  std::stringstream ss;
  ss << "Provided path " << provided_path << " is not in a git repository.";
  throw std::runtime_error(ss.str());
}

};
