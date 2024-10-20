#include "trie.hpp"

#include <stdexcept>

Trie::Trie() : begin(new Vertex) {}
Trie::~Trie() { delete begin; }

Trie::Vertex::Vertex() : next(256, nullptr), is_terminal(false) {}
Trie::Vertex::~Vertex() {
  for (auto vertex : next) {
    delete vertex;
  }
}

void Trie::insert(const std::string& s) {
  auto vertex(begin);
  for (char c : s) {
    if (vertex->next[c] == nullptr) {
      vertex->next[c] = new Vertex;
    }
    vertex = vertex->next[c];
  }
  vertex->is_terminal = true;
}

bool Trie::contains(const std::string& s) const {
  auto vertex(begin);
  for (char c : s) {
    if (vertex->next[c] == nullptr) {
      return false;
    }
    vertex = vertex->next[c];
  }
  return vertex->is_terminal;
}
