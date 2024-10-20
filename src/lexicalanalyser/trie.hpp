#pragma once

#include <vector>
#include <string>

class Trie {
 public:
  Trie();
  ~Trie();

  void insert(const std::string &);
  bool contains(const std::string &) const;

 private:
  struct Vertex {
    Vertex();
    ~Vertex();

    std::vector<Vertex *> next;
    bool is_terminal;
  };

  Vertex* begin;
};
