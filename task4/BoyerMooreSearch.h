#ifndef BOYERMOORESEARCH_H
#define BOYERMOORESEARCH_H

class BoyerMooreSearch {
    std::vector<int> symbol_table;
    std::vector<int> suffix_table;

    void fill_symbol_table(std::string pattern);
    void fill_suffix_table(std::string pattern);
public:
    void search(std::string pattern, std::string line);
    void turbo_search(std::string pattern, std::string line);
    void print_symbol_table();
    void print_suffix_table();
};

#endif //BOYERMOORESEARCH_H
