#include <cstring>
#include <format>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <pthread.h>
#include <sstream>
#include <string>
#include <vector>

#include "argparser.hpp"
#include "utils.hpp"

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

std::vector<std::string> ap::ArgParser::validate_arguments(int argc, char* argv[]) {
  std::vector<std::string> cleaned_args;
  bool last_readed_arg_needs_value = false;

  for (int i = 1; i < argc; i++) {
    auto arg = argv[i];
    bool is_short_arg = start_with(arg, "-");
    bool is_long_arg = start_with(arg, "--");

    if (is_short_arg && !is_long_arg && !last_readed_arg_needs_value) {
      int arg_length = strlen(arg);

      // if args_legth == 1; is because the user pass only "-" you should append too in this case
      // other option is return a error for example missing arg option
      if (arg_length == 1) {
        cleaned_args.push_back(arg);
      }

      for (int k = 1; k < arg_length; k++) {
        auto* current_option = find_option_by_name(arg);
        cleaned_args.push_back(std::format("-{}", arg[k]));
        if (current_option != nullptr) {
          last_readed_arg_needs_value
            = current_option->type == ap::INT;  // for now only int needs a value
        } else {
          last_readed_arg_needs_value = false;
        }
      }
    } else {
      cleaned_args.push_back(arg);
      auto* current_option = find_option_by_name(arg);
      if (current_option != nullptr) {
        last_readed_arg_needs_value
          = current_option->type == ap::INT;  // for now only int needs a value
      } else {
        last_readed_arg_needs_value = false;
      }
    }
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

bool ap::ArgParser::has_error() { return errors.size() > 0; }

void ap::ArgParser::add_error(std::string description,
                              ap::argoption* option,
                              std::string value,
                              ArgOptionTypeError code) {
  errors.push_back(argerror{ description, option, value, code });
}

std::string ap::ArgParser::show_errors() {
  // 0 - types of error not found argument
  // 1 - invalid argumnent option
  // 2 - missing value argument option
  std::ostringstream oss;

  for (auto& error : errors) {
    std::ostringstream error_message;
    switch (error.code) {
    case NOT_FOUND_ARGUMENT:
      error_message << "Unknown argument " << error.input;
      break;
    case INVALID_ARGUMENT_OPTION:
      error_message << "Value " << std::format("\"{}\"", error.input) << " not valid for option "
                    << error.option->short_name << ": " << error.description;
      break;
    case MISSING_VALUE_ARGUMENT_OPTION:
      error_message << "Flag " << error.option->short_name << " needs a value";
      break;
    }

    oss << "argparser: " << error_message.str() << "\n";
  }

  return oss.str();
}

int ap::ArgParser::get_options_size() { return options.size(); }

bool ap::ArgParser::parser(int argc, char* argv[]) {
  auto validaded_args = validate_arguments(argc, argv);
  int left = 0;
  int rigth = validaded_args.size();

  while (left < rigth) {
    auto arg = validaded_args[left];
    argoption* opt = nullptr;
    opt = find_option_by_name(arg);

    if (opt != nullptr) {
      switch (opt->type) {
      case BOOL:
        *static_cast<bool*>(opt->value) = true;
        break;
      case INT:
        // TODO: Refact to remove this if else
        if (left + 1 >= validaded_args.size()) {
          add_error("", opt, "", ap::MISSING_VALUE_ARGUMENT_OPTION);
          return false;
        } else {
          auto arg_val = validaded_args[left + 1];

          if (!is_valid_interger(arg_val)) {
            add_error("Invalid digit found in string", opt, arg_val, ap::INVALID_ARGUMENT_OPTION);
            return false;
          }

          auto arg_val_parsed = std::stoi(arg_val);
          *static_cast<int*>(opt->value) = arg_val_parsed;
          left++;
        }
        break;
      }
    } else {
      add_error("", nullptr, arg, NOT_FOUND_ARGUMENT);
      return false;
    }

    left++;
  }

  return true;
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
        // subsequent wrapped lines indent to description column
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
