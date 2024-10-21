#pragma once

#include <string>
#include <vector>

struct TrieVertex {
  TrieVertex();
  ~TrieVertex();

  std::vector<TrieVertex *> next;
  bool is_terminal;
};

class Trie {
 public:
  Trie();
  ~Trie();

  void Insert(const std::string &);
  bool Contains(const std::string &) const;

 private:
  TrieVertex *begin_;
};
