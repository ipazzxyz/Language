add_executable(tests
    test.cpp
    trie.cpp trie.hpp
)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
