#pragma once

#include <cstddef>
#include <string>

enum class LexemeType {
  kKeyword,
  kIdentifier,
  kStringLiteral,
  kNumberLiteral,
  kOperator,
  kPunctuation,
  kComma,
  kDot,
  kDotComma,
  kRoundBracket,
  kCurlyBracket,
  kUndefined
};

struct Lexeme {
  std::string text;
  LexemeType type;
  std::size_t line;
};
