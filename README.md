# argparser
Simple CLI arguments parser C++

## Usage
```cpp
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
```
```
```
```
```

## TODO
- [ ] Add cli argument handler
- [ ] Refact struct the code better with classes and split code definitions and implementations
- [ ] Handle multiples short options like -fabs (if valid should combine each) (> [!NOTE]
> Talvez implementar uma fila para guardar a ordem de cada argumento)
  -  RULE: Args that need a specific value should separeted never combined (Limition for simplify)
- [ ] Add tests
- [ ] Add error handler ArgParser.has_error and should store errors of the current cycle (ok = parser(argc, argv) -> if(!ok) argParser.showErrors())
- [ ] Add validation callback for validate a input value like length of password, should be > 0
- [x] Add help usage
- [x] Add option description or help text
- [ ] Refactor to optimize the code and check memory lick, improve pointer access operations, etc...
- [ ] Add Documentation
- [x] Handle bool values
- [x] Handle integer values
```
