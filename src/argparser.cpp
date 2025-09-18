#include <iostream>
#include <string>
#include <vector>

namespace ap {

enum ArgOptionType { BOOL, STRING, INT };

struct argoption {
  std::string short_name;
  std::string long_name;
  void *value;
  ArgOptionType type;
};

class ArgParser {
private:
  std::vector<argoption> options;

  bool start_with(std::string value, std::string symbol) {
    if (value.size() < symbol.size())
      return false;

    for (int i = 0; i < symbol.size(); i++) {
      if (value[i] != symbol[i]) {
        return false;
      }
    }

    return true;
  }

  argoption *find_option_by_name(std::string name) {
    for (auto &opt : options) {
      std::cout << opt.long_name << "\n";
      if (opt.short_name == name || opt.long_name == name) {
        return &opt;
      }
    }

    return nullptr;
  }

public:
  void add_arguments(std::string short_name, std::string long_name, void *value,
                     ArgOptionType type) {
    options.push_back(argoption{short_name, long_name, value, type});
  }

  void parser(int argc, char *argv[]) {
    int left = 0;
    int rigth = argc;

    while (left < rigth) {
      auto arg = argv[left];
      argoption *opt = nullptr;
      opt = find_option_by_name(arg);

      // TODO: Handle multiples shortargs like -hpxa
      // TODO: Handle repeated args should ignore and exec the action only one
      // time (Maybe create a function exact for clean the input before? for
      // example and return a cleaned arg list with all passing options)

      if (opt != nullptr) {
        switch (opt->type) {
        case BOOL:
          *static_cast<bool *>(opt->value) = true;
          break;
        case INT:
          // handle bool or string value
          // for example for string interger value the next arg should be the
          // should validate if exists
          // TODO: Refact to remove this if else

          // TODO: Should validate if next arg is valid value, use some way to
          // validate if is a valid interger, because stoi maybe trucate the
          // value to a interger passing a decimal value like 10.5

          if (left + 1 >= argc) {
            // TODO: Implement result pattern like Go (ok, err);
            // throw error for example argument invalid
            std::cout << "é preciso dizer um valor essa flag." << "\n";
          } else {
            // handle possible exceptions like (10a...) try_catch
            auto arg_val = std::stoi(argv[left + 1]);
            *static_cast<int *>(opt->value) = arg_val;
            left++;
          }

          break;
        case STRING:
          break;
        }
      }

      left++;
    }
  }
};
} // namespace ap
