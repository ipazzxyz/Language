#include "trie.hpp"

TrieVertex::TrieVertex() : next(256, nullptr), is_terminal(false) {}

TrieVertex::~TrieVertex() {
  for (auto vertex : next) {
    delete vertex;
  }
}

Trie::Trie() : begin_(new TrieVertex) {}

Trie::~Trie() { delete begin_; }

void Trie::Insert(const std::string &s) {
  auto vertex(begin_);
  for (auto c : s) {
    if (vertex->next[c] == nullptr) {
      vertex->next[c] = new TrieVertex;
    }
    vertex = vertex->next[c];
  }
  vertex->is_terminal = true;
}

bool Trie::Contains(const std::string &s) const {
  auto vertex(begin_);
  for (auto c : s) {
    if (vertex->next[c] == nullptr) {
      return false;
    }
    vertex = vertex->next[c];
  }
  return vertex->is_terminal;
}
