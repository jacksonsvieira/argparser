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


## Running

```c++
clang++ -std=c++20 src/argparser.cpp src/demo.cpp
```

## References
- [Python argparser](https://docs.python.org/3/library/argparse.html) Where the curiosity came from
- [Argparser C lib](https://github.com/cofyc/argparse/blob/master/tests/basic.c#L25) Usefull insigths and idea of generic pointers
- [Eza](https://github.com/eza-community/eza.git) Used as inspiration in error message output when invalid args are pass


## Contributing

Contribuitions and new ideas are welcome!

## TODO
- [x] Add cli argument handler
- [x] Refact struct the code better with classes and split code definitions and implementations
- [x] Handle multiples short options like -fabs (if valid should combine each) (> [!NOTE]
> Talvez implementar uma fila para guardar a ordem de cada argumento)
  -  RULE: Args that need a specific value should separeted never combined (Limition for simplify)
- [x] Add error handler ArgParser.has_error and should store errors of the current cycle (ok = parser(argc, argv) -> if(!ok) argParser.showErrors())
- [x] Add help usage
- [x] Add option description or help text
- [x] Handle bool values
- [x] Handle integer values
- [ ] Add tests
- [ ] Add Documentation

## Ideas
- [ ] Add validation callback for validate a input value like length of password, should be > 0
- [ ] Import config from a file .ini
