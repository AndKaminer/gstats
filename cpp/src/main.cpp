#include <CLI/CLI.hpp>

int main(int argc, char** argv) {
  CLI::App app{"A git statistics aggregator"};
  app.require_subcommand();

  auto* count_files {app.add_subcommand("count-files", "Count the number of files in the project.")};
  auto* count_lines {app.add_subcommand("count-lines", "Count the lines of code in the project, aggregated in various ways.")};
  auto* repository_size {app.add_subcommand("repo-size", "Calculate the size of the repository.")};
  auto* show_files {app.add_subcommand("show-files", "List the files in the repository, ordered in various ways.")};
  auto* count_commits {app.add_subcommand("count-commits", "Count commits in the repository, aggregated in various ways.")};

  CLI11_PARSE(app, argc, argv);

  return 0;
}
