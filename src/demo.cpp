#include <cstdlib>
#include <iostream>
#include "./argparser.hpp"

int main(int argc, char* argv[]) {
  bool show_help = false;
  int password_length = 7;

  ap::ArgParser argParser("passgen", "simple cli password generator", "0.0.1");
  argParser.add_arguments("-h", "--help", "show help", &show_help, ap::BOOL);
  argParser.add_arguments("-l", "--len", "set password size", &password_length, ap::INT);
  bool ok = argParser.parser(argc, argv);

  if (!ok) {
    // TODO: Create a method "show_errors"
    for (auto& error : argParser.get_errors()) {
      std::cout << error.description << "\n";
    }

    return EXIT_FAILURE;
  }

  if (show_help) {
    auto usage = argParser.usage();
    std::cout << usage;
  }

  return EXIT_SUCCESS;
}
