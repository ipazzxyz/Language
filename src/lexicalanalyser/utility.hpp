#pragma once

#include <string>
#include <set>

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

std::string FormatString(const std::string &string) {
    std::string result;
    std::set<char> special_characters = {'(', ')', '{', '}', '.', ',', ';'};
    char last_symbol;
    for (char c : string) {
        if (c == '\n') continue;

        if (last_symbol == ' ') {
            if (c == ' ') continue;
            if (special_characters.find(c) != special_characters.end()) {
                result += c;
                result += ' ';
                continue;
            }
            result += c;
            last_symbol = c;
        } else {
            if (special_characters.find(c) != special_characters.end()) {
                result += ' ';
                result += c;
                result += ' ';
                last_symbol = ' ';
                continue;
            }
            result += c;
            last_symbol = c;
        }
    }
    return result;
}
}  // namespace utility
