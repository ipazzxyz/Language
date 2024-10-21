add_executable(tests
    test.cpp
    lexicalanalyser.cpp
    trie.cpp
)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
