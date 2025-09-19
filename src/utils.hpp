#include <algorithm>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

inline bool is_numeric_all_of(const std::string& str) {
  if (str.empty()) {
    return false;
  }

  return std::all_of(str.begin(), str.end(), ::isdigit);  // Use ::isdigit for global scope
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
