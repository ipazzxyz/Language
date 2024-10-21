#include "lexicalanalyser.hpp"

#include <fstream>
#include <sstream>

#include "keywords.hpp"
#include "operators.hpp"

LexicalAnalyser::LexicalAnalyser() {
  for (auto keyword : kKeywords) {
    keywords_.Insert(keyword);
  }
  for (auto Operator : kOperators) {
    operators_.Insert(Operator);
  }
}

void LexicalAnalyser::FromFile(const std::string& filename) {
  std::ifstream file(filename);
  file.seekg(0, file.end);
  text_.resize(file.tellg());
  file.seekg(0, file.beg);
  file.read(&text_[0], text_.size());
  file.close();
  BreakIntoLexemes();
}

void LexicalAnalyser::FromText(const std::string& text) {
  text_ = text;
  BreakIntoLexemes();
}

const std::vector<Lexeme>& LexicalAnalyser::GetLexemes() const {
  return lexemes_;
}

void LexicalAnalyser::BreakIntoLexemes() {
  std::stringstream textbuf(text_);
  Lexeme lexeme;
  lexeme.line = 0;
  std::string line;
  while (++lexeme.line, getline(textbuf, line)) {
    std::stringstream linebuf(line);
    while (linebuf >> lexeme.text) {
      if (keywords_.Contains(lexeme.text)) {
        lexeme.type = LexemeType::kKeyword;
      } else if (operators_.Contains(lexeme.text)) {
        lexeme.type = LexemeType::kOperator;
      } else if (lexeme.text == "(") {
        lexeme.type = LexemeType::kBracketOpen;
      } else if (lexeme.text == ")") {
        lexeme.type = LexemeType::kBracketClose;
      } else if (lexeme.text == ".") {
        lexeme.type = LexemeType::kDot;
      } else if (lexeme.text == ",") {
        lexeme.type = LexemeType::kComma;
      } else if (lexeme.text == ";") {
        lexeme.type = LexemeType::kDotComma;
      } else {
        lexeme.type = LexemeType::kIdentifier;
      }
      lexemes_.push_back(lexeme);
    }
  }
}
