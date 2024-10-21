#pragma once

#include <vector>

#include "lexeme.hpp"
#include "trie.hpp"

class LexicalAnalyser {
 public:
  LexicalAnalyser();

  void FromFile(const std::string& filename);
  void FromText(const std::string& text);

  const std::vector<Lexeme>& GetLexemes() const;

 private:
  std::string text_;
  Trie keywords_;
  Trie operators_;
  std::vector<Lexeme> lexemes_;

  void BreakIntoLexemes();
};
