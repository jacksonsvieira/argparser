#include <string>
#include <vector>

namespace ap {

enum ArgOptionType { BOOL, STRING, INT };

struct argoption {
  std::string short_name;
  std::string long_name;
  void* value;
  ArgOptionType type;
};

class ArgParser {
private:
  std::vector<argoption> options;

  bool start_with(std::string value, std::string symbol);
  argoption* find_option_by_name(std::string name);
  std::vector<std::string> clear_arguments(int argc, char* argv[]);

public:
  void add_arguments(std::string short_name,
                     std::string long_name,
                     void* value,
                     ArgOptionType type);

  void parser(int argc, char* argv[]);

  int get_options_size();

  std::string usage();
};
}  // namespace ap
