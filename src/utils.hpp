#include <algorithm>
#include <cctype>
#include <string>

inline bool is_numeric_all_of(const std::string& str) {
  if (str.empty()) {
    return false;
  }
  return std::all_of(str.begin(), str.end(), ::isdigit);  // Use ::isdigit for global scope
}
