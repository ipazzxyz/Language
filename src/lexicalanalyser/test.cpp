#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "lexicalanalyser.hpp"
#include "trie.hpp"

TEST_CASE("Trie") {
  Trie trie;
  trie.Insert("a");
  trie.Insert("aaa");
  trie.Insert("abcdef");
  REQUIRE(trie.Contains("a") == true);
  REQUIRE(trie.Contains("aa") == false);
  REQUIRE(trie.Contains("aaa") == true);
  REQUIRE(trie.Contains("aaaa") == false);
  REQUIRE(trie.Contains("abb") == false);
  REQUIRE(trie.Contains("abcdef") == true);
}

TEST_CASE("Lexical Analiser") {
  LexicalAnalyser lexicalanaliser;
  lexicalanaliser.FromText("int qwerty ;\nqwerty = qwerty + 1 ;");
  auto lexemes(lexicalanaliser.GetLexemes());
  REQUIRE(lexemes.size() == 9);
  REQUIRE(lexemes[0].line == 1);
  REQUIRE(lexemes[0].text == "int");
  REQUIRE(lexemes[0].type == LexemeType::kKeyword);
  REQUIRE(lexemes[1].line == 1);
  REQUIRE(lexemes[1].text == "qwerty");
  REQUIRE(lexemes[1].type == LexemeType::kIdentifier);
  REQUIRE(lexemes[2].line == 1);
  REQUIRE(lexemes[2].text == ";");
  REQUIRE(lexemes[2].type == LexemeType::kDotComma);
  REQUIRE(lexemes[3].line == 2);
  REQUIRE(lexemes[3].text == "qwerty");
  REQUIRE(lexemes[3].type == LexemeType::kIdentifier);
  REQUIRE(lexemes[4].line == 2);
  REQUIRE(lexemes[4].text == "=");
  REQUIRE(lexemes[4].type == LexemeType::kOperator);
  REQUIRE(lexemes[5].line == 2);
  REQUIRE(lexemes[5].text == "qwerty");
  REQUIRE(lexemes[5].type == LexemeType::kIdentifier);
  REQUIRE(lexemes[6].line == 2);
  REQUIRE(lexemes[6].text == "+");
  REQUIRE(lexemes[6].type == LexemeType::kOperator);
  REQUIRE(lexemes[7].line == 2);
  REQUIRE(lexemes[7].text == "1");
  // REQUIRE(lexemes[7].type == LexemeType::kLiteral);
  REQUIRE(lexemes[8].line == 2);
  REQUIRE(lexemes[8].text == ";");
  REQUIRE(lexemes[8].type == LexemeType::kDotComma);
}
