#include "lexicalanalyser.hpp"

#include <fstream>
#include <sstream>

#include "keywords.hpp"
#include "operators.hpp"
#include "utility.hpp"

LexicalAnalyser::LexicalAnalyser() {
  for (auto keyword : kKeywords) {
    keywords_.Insert(keyword);
  }
  for (auto Operator : kOperators) {
    operators_.Insert(Operator);
  }
}

void LexicalAnalyser::FromFile(const std::string &filename) {
  std::ifstream file(filename);
  file.seekg(0, file.end);
  text_.resize(file.tellg());
  file.seekg(0, file.beg);
  file.read(
      &text_[0],
      text_
          .size());  // Can do so since C++11
                     // (https://stackoverflow.com/questions/1986966/does-s0-point-to-contiguous-characters-in-a-stdstring)
  file.close();
  BreakIntoLexemes();
}

void LexicalAnalyser::FromText(const std::string &text) {
  text_ = text;
  BreakIntoLexemes();
}

const std::vector<Lexeme> &LexicalAnalyser::GetLexemes() const {
  return lexemes_;
}

void LexicalAnalyser::BreakIntoLexemes() {
  lexemes_.clear();
  std::stringstream textbuf(text_);
  Lexeme lexeme;
  lexeme.line = 0;
  std::string line;
  while (++lexeme.line, getline(textbuf, line)) {
    std::stringstream linebuf(utility::FormatString(line));
    while (linebuf >> lexeme.text) {
      if (keywords_.Contains(lexeme.text)) {
        lexeme.type = LexemeType::kKeyword;
      } else if (operators_.Contains(lexeme.text)) {
        lexeme.type = LexemeType::kOperator;
      } else if (lexeme.text[0] == '"') {
        lexeme.type = LexemeType::kStringLiteral;
        if (lexeme.text[lexeme.text.size() - 1] != '"') {
          std::size_t g = linebuf.tellg(), find = line.find('"', g);
          lexeme.text += (line.substr(g, find - g + 1));
          linebuf.seekg(find + 1);
        }
        lexeme.text.erase(lexeme.text.begin());
        lexeme.text.pop_back();
      } else if (utility::IsNumber(lexeme.text)) {
        lexeme.type = LexemeType::kNumberLiteral;
      } else if (lexeme.text == "(" || lexeme.text == ")") {
        lexeme.type = LexemeType::kRoundBracket;
      } else if (lexeme.text == "{" || lexeme.text == "}") {
        lexeme.type = LexemeType::kCurlyBracket;
      } else if (lexeme.text == ".") {
        lexeme.type = LexemeType::kDot;
      } else if (lexeme.text == ",") {
        lexeme.type = LexemeType::kComma;
      } else if (lexeme.text == ";") {
        lexeme.type = LexemeType::kDotComma;
      } else if (utility::IsIdentifier(lexeme.text)) {
        lexeme.type = LexemeType::kIdentifier;
      } else {
        lexeme.type = LexemeType::kUndefined;
      }
      lexemes_.push_back(lexeme);
    }
  }
}
