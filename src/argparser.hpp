#include <string>
#include <vector>

namespace ap {

enum ArgOptionType { BOOL, INT };

struct argoption {
  std::string short_name;
  std::string long_name;
  std::string description;
  void* value;
  ArgOptionType type;
};

class ArgParser {
private:
  std::vector<argoption> options;

  std::string project_name;
  std::string project_brief_description;
  std::string project_version;

  bool start_with(std::string value, std::string symbol);
  argoption* find_option_by_name(std::string name);
  std::vector<std::string> validate_arguments(int argc, char* argv[]);

public:
  ArgParser(std::string project_name,
            std::string project_brief_description,
            std::string project_version) {
    this->project_name = project_name;
    this->project_brief_description = project_brief_description;
    this->project_version = project_version;
  }

  void add_arguments(std::string short_name,
                     std::string long_name,
                     std::string description,
                     void* value,
                     ArgOptionType type);

  void parser(int argc, char* argv[]);

  int get_options_size();

  std::string usage();
};
}  // namespace ap
