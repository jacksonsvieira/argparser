#include <cstring>
#include <format>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

#include "argparser.h"

bool ap::ArgParser::start_with(std::string value, std::string symbol) {
  if (value.size() < symbol.size())
    return false;

  for (int i = 0; i < symbol.size(); i++) {
    if (value[i] != symbol[i]) {
      return false;
    }
  }

  return true;
}

ap::argoption* ap::ArgParser::find_option_by_name(std::string name) {
  for (auto& opt : options) {
    if (opt.short_name == name || opt.long_name == name) {
      return &opt;
    }
  }

  return nullptr;
}

std::vector<std::string> ap::ArgParser::clear_arguments(int argc, char* argv[]) {
  std::vector<std::string> cleaned_args;
  std::unordered_map<std::string, bool> args_filled;

  // TODO: maybe this function should validate for example if a arg option
  // exists for a given arg, maybe validate repetions based on the values,
  // return result approach, for example if have some error create a list of
  // error and create a msg error for each argument

  // argerror (arg_name, error description)
  // always have a pointer to the last option get

  for (int i = 1; i < argc; i++) {
    auto arg = argv[i];
    bool is_short_arg = start_with(arg, "-");
    bool is_long_arg = start_with(arg, "--");

    // bool already_readed = args_filled.count(arg);
    // if (already_readed)
    //   continue;

    if (is_short_arg) {
      int arg_length = strlen(arg);
      for (int k = 1; k < arg_length; k++) {
        cleaned_args.push_back(std::format("-{}", arg[k]));
      }
    } else if (is_long_arg) {
      cleaned_args.push_back(arg);
    } else {
      cleaned_args.push_back(arg);
    }

    args_filled[arg] = true;
  }

  return cleaned_args;
}

void ap::ArgParser::add_arguments(std::string short_name,
                                  std::string long_name,
                                  std::string description,
                                  void* value,
                                  ArgOptionType type) {
  options.push_back(ap::argoption{ short_name, long_name, description, value, type });
}

int ap::ArgParser::get_options_size() { return options.size(); }

void ap::ArgParser::parser(int argc, char* argv[]) {
  auto validaded_args = clear_arguments(argc, argv);

  int left = 0;
  int rigth = validaded_args.size();

  while (left < rigth) {
    auto arg = validaded_args[left];
    argoption* opt = nullptr;
    opt = find_option_by_name(arg);

    // TODO: Handle repeated args should ignore and exec the action only one
    // time (Maybe create a function exact for clean the input before? for
    // example and return a cleaned arg list with all passing options)
    // TODO: Handle multiples shortargs like -hpxa

    if (opt != nullptr) {
      switch (opt->type) {
      case BOOL:
        *static_cast<bool*>(opt->value) = true;
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
          auto arg_val = std::stoi(validaded_args[left + 1]);
          *static_cast<int*>(opt->value) = arg_val;
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

int COL_OPTION_INFO_WIDTH = 40;
int COL_OPTION_DESCRIPTION_MAX_WIDTH = 80;

std::vector<std::string> wrap_text(std::string text, int width) {
  std::istringstream stream(text);
  std::vector<std::string> wrapped;

  std::string current;
  std::string word;

  while (stream >> word) {
    if (current.empty()) {
      current = word;
    } else {
      if (current.size() + word.size() + 1 > width) {
        wrapped.push_back(current);
        current = word;
      } else {
        current += " " + word;
      }
    }
  }

  // fallback
  if (!current.empty())
    wrapped.push_back(current);

  return wrapped;
}

std::string ap::ArgParser::usage() {

  const size_t total_width = 80;
  const size_t left_col_width = 28;
  const size_t desc_width
    = (total_width > left_col_width + 2) ? (total_width - left_col_width - 2) : 40;

  std::ostringstream oss;

  oss << project_name << "  v" << project_version << "\n";
  oss << project_brief_description << "\n\n";

  oss << "Usage: " << project_name << " [<options>]\n\n";
  oss << "Options:\n";

  for (auto& opt : options) {
    std::string left;
    if (!opt.short_name.empty() && !opt.long_name.empty()) {
      left = opt.short_name + ", " + opt.long_name;
    } else if (!opt.long_name.empty()) {
      left = opt.long_name;
    } else {
      left = opt.short_name;
    }

    // put left in the entire fow if is larger than left col width
    if (left.size() >= left_col_width) {
      oss << "  " << left << "\n";
      auto wrapped = wrap_text(opt.description, desc_width);
      for (const auto& line : wrapped) {
        oss << std::setw((int)left_col_width + 2) << "" << line << "\n";
      }
    } else {
      auto wrapped = wrap_text(opt.description, desc_width);

      std::ostringstream leftoss;
      leftoss << "  " << std::left << std::setw((int)left_col_width) << left;
      std::string leftcol = leftoss.str();

      if (!wrapped.empty()) {
        oss << leftcol << "  " << wrapped[0] << "\n";
        // subsequent wrapped lines: indent to description column
        for (size_t i = 1; i < wrapped.size(); ++i) {
          oss << std::setw(left_col_width + 2) << "" << wrapped[i] << "\n";
        }
      } else {
        oss << leftcol << "\n";
      }
    }
  }

  return oss.str();
}
