#include <string>
#include <vector>

namespace ap {

enum ArgOptionType { BOOL, INT };

// 0 - types of error not found argument
// 1 - invalid argumnent option
// 2 - missing value argument option
enum ArgOptionTypeError {
  NOT_FOUND_ARGUMENT,
  INVALID_ARGUMENT_OPTION,
  MISSING_VALUE_ARGUMENT_OPTION
};

struct argoption {
  std::string short_name;
  std::string long_name;
  std::string description;
  void* value;
  ArgOptionType type;
};

struct argerror {
  std::string description;
  argoption* option;
  std::string input;
  ArgOptionTypeError code;
};

class ArgParser {
private:
  std::vector<argoption> options;
  std::vector<argerror> errors;

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

  bool parser(int argc, char* argv[]);

  int get_options_size();

  bool has_error();

  void add_error(std::string description,
                 argoption* option,
                 std::string value,
                 ArgOptionTypeError code);

  std::string show_errors();

  std::string usage();
};
}  // namespace ap
