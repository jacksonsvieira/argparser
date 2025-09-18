#include "./argparser.cpp"
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[]) {
  ap::argoption options[1] = {ap::argoption{}};
  bool show_help = false;
  int password_length = 7;

  ap::ArgParser argParser;
  argParser.add_arguments("-h", "--help", &show_help, ap::BOOL);
  argParser.add_arguments("-l", "--len", &password_length, ap::INT);
  argParser.parser(argc, argv);

  std::cout << "Show help: " << (show_help ? "sim" : "não") << "\n";
  std::cout << "Tamanho da senha: " << password_length << "\n";

  return EXIT_SUCCESS;
}
