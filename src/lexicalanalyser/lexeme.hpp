#pragma once

#include <cstddef>
#include <string>

enum class LexemeType {
  kKeyword,
  kIdentifier,
  kLiteral,
  kOperator,
  kPunctuation,
  kComma,
  kDot,
  kBracketOpen,
  kBracketClose,
  kDotComma,
  kUndefined
};

struct Lexeme {
  std::string text;
  LexemeType type;
  std::size_t line;
};
