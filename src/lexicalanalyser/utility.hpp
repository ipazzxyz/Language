#pragma once

#include <string>

namespace utility {
inline bool IsNumber(const std::string &string) {
  if (string == "+" || string == "-") {
    return false;
  }
  for (std::size_t i = string[0] == '-' || string[0] == '+' ? 1 : 0;
       i < string.size(); ++i) {
    if (!std::isdigit(string[i])) {
      return false;
    }
  }
  return true;
}

inline bool IsIdentifier(const std::string &string) {
  if (!std::islower(string[0]) && !std::isupper(string[0])) {
    return false;
  }
  for (auto c : string) {
    if (!std::islower(c) && !std::isupper(c) && !std::isdigit(c)) {
      return false;
    }
  }
  return true;
}
}  // namespace utility
