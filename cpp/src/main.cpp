#include <CLI/CLI.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "repository.hpp"
#include "index.hpp"

int main(int argc, char** argv) {
  std::filesystem::path repo_base_directory = std::filesystem::current_path();

  CLI::App app{"A git statistics aggregator"};
  app.require_subcommand();
  app.parse_complete_callback([&]() {
    repo_base_directory = std::filesystem::absolute(repo_base_directory);
    repo_base_directory = repository::get_repository_base(repo_base_directory);
  });


  app.add_option(
    "-p,--repo-path",
    repo_base_directory,
    "A path inside of the git directory you want to check."
  )->check(CLI::ExistingPath);

  auto* count_files {app.add_subcommand(
    "count-files",
    "Count the number of files in the project."
  )};
  auto* count_lines {app.add_subcommand(
    "count-lines",
    "Count the lines of code in the project, aggregated in various ways."
  )};
  auto* repository_size {app.add_subcommand(
    "repo-size",
    "Calculate the size of the repository."
  )};
  auto* show_files {app.add_subcommand(
    "show-files",
    "List the files in the repository, ordered in various ways."
  )};
  auto* count_commits {app.add_subcommand(
    "count-commits",
    "Count commits in the repository, aggregated in various ways."
  )};

  CLI11_PARSE(app, argc, argv);

  git_index::read_index_file(repo_base_directory / ".git" / "index");
  return 0;
}
