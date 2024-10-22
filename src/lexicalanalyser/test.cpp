#include <catch2/catch_test_macros.hpp>

#include "lexicalanalyser.hpp"
#include "trie.hpp"
#include "utility.hpp"

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

TEST_CASE("Utility function") {
  SECTION("IsNumber") {
    REQUIRE(utility::IsNumber("1337") == true);
    REQUIRE(utility::IsNumber("+1337") == true);
    REQUIRE(utility::IsNumber("01337") == true);
    REQUIRE(utility::IsNumber("qwe") == false);
    REQUIRE(utility::IsNumber("-420") == true);
    REQUIRE(utility::IsNumber("+13.37") == false);
    REQUIRE(utility::IsNumber("-1") == true);
    REQUIRE(utility::IsNumber("+") == false);
  }
  SECTION("IsIdentifier") {
    REQUIRE(utility::IsIdentifier("qwerty") == true);
    REQUIRE(utility::IsIdentifier("qwerty42") == true);
    REQUIRE(utility::IsIdentifier("42qwerty") == false);
    REQUIRE(utility::IsIdentifier("привет") == false);
    REQUIRE(utility::IsIdentifier("+") == false);
  }
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
  REQUIRE(lexemes[7].type == LexemeType::kNumberLiteral);
  REQUIRE(lexemes[8].line == 2);
  REQUIRE(lexemes[8].text == ";");
  REQUIRE(lexemes[8].type == LexemeType::kDotComma);
  SECTION("String literals") {
    lexicalanaliser.FromText("\"qwe\"");
    lexemes = lexicalanaliser.GetLexemes();
    REQUIRE(lexemes[0].text == "qwe");
    REQUIRE(lexemes[0].type == LexemeType::kStringLiteral);
    lexicalanaliser.FromText("\"qwe asd\"");
    lexemes = lexicalanaliser.GetLexemes();
    REQUIRE(lexemes[0].text == "qwe asd");
    lexicalanaliser.FromText("\"zxc\" \"993 986\" 979 \"let me die :(   \"");
    lexemes = lexicalanaliser.GetLexemes();
    REQUIRE(lexemes[0].text == "zxc");
    REQUIRE(lexemes[1].text == "993 986");
    REQUIRE(lexemes[2].text == "979");
    REQUIRE(lexemes[2].type == LexemeType::kNumberLiteral);
    REQUIRE(lexemes[3].text == "let me die :(   ");
  }
  SECTION("Undefined") {
    lexicalanaliser.FromText("Привет!!!");
    lexemes = lexicalanaliser.GetLexemes();
    REQUIRE(lexemes[0].type == LexemeType::kUndefined);
  }
}
