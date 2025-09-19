#include <cstdlib>
#include <iostream>
#include "./argparser.h"

int main(int argc, char* argv[]) {
  bool show_help = false;
  int password_length = 7;

  ap::ArgParser argParser("passgen", "simple cli password generator", "0.0.1");
  argParser.add_arguments("-h", "--help", "show help", &show_help, ap::BOOL);
  argParser.add_arguments("-l", "--len", "set password size", &password_length, ap::INT);
  argParser.parser(argc, argv);

  if (show_help) {
    auto usage = argParser.usage();
    std::cout << usage;
  }

  return EXIT_SUCCESS;
}
