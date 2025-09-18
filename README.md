# argparser
Simple command line arguments parser to c++

## Instalattion

Colocar um guia de como instalar a lib no projeto

## Usage
```cpp

int main(int argc, char[] argv){
  ap::argoption options[1] = {ap::argoption{}};
  bool show_help = false;
  int password_length = 7;

  // options[0].long_name = "--help";
  // options[0].short_name = "-h";
  // options[0].value = &show_help;
  // options[0].type = ap::BOOL;

  options[0].long_name = "--length";
  options[0].short_name = "-l";
  options[0].value = &password_length;
  options[0].type = ap::INT;

  ap::argparser(argc, argv, options);
  std::cout << (show_help ? "HELP!" : "Pro play!") << "\n";
  std::cout << "Tamanho da senha: " << password_length << "\n";
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
- [ ] Add exception handler
- [ ] Add help usage
- [ ] Add option description or help text
- [ ] Refactor to optimize the code and check memory lick, improve pointer access operations, etc...
- [ ] Add Documentation
- [x] Handle bool values
- [x] Handle integer values
```
