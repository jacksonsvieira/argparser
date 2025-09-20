#include <cctype>
#include <sstream>
#include <string>
#include <vector>

inline bool is_valid_interger(const std::string& str) {
  int i = 0;

  if (str.empty()) {
    return false;
  }

  if (str[i] == '+' || str[i] == '-') {
    i = 1;
  }

  // left = 1 and size = 1 is invalid because contains only the sign
  if (i == str.size()) {
    return false;
  }

  for (; i < str.size(); i++) {
    if (!isdigit(str[i])) {
      return false;
    }
  }

  return true;
}

inline std::vector<std::string> wrap_text(std::string text, int width) {
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
