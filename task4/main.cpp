#include <iostream>
#include <vector>
#include <sstream>

#include "BoyerMooreSearch.h"

using namespace std;

// Определение "расстояния" между парами слов
int get_distance(string s1, string s2) {
    int value = 0;
    int len1 = s1.length();
    int len2 = s2.length();

    // Сравниваем по символам в одинаковой позиции
    for (int i = 0; i < min(len1, len2); i++) {
        if (s1[i] != s2[i])
            value++;
    }

    // Вычисляем расстояние как разницу между строками и разницу их длин
    return value + abs(len1 - len2);
}

// Поиск пары слов с минимальным расстоянием
string get_min_distance_pairs(string line) {
    vector<string> words;
    string str;
    istringstream ist(line);
    string word;
    // Разбиваем строку на слова и записываем их в вектор words
    while (ist >> word) {
        if (word[word.length() - 1] == ',' || word[word.length() - 1] == '.')
            word = word.substr(0,word.length() - 1);
        words.push_back(word);
    }

    int min_val = -1;
    int distance = 0;
    string s1, s2;
    // Начинаем сравнивать пары слов и записывать мин. расстояние
    for (int i = 0; i < words.size(); i++) {
        for (int j = i + 1; j < words.size(); j++) {
            distance = get_distance(words[i], words[j]);

            if ((i == 0 && j == 1) || (distance < min_val)) {
                min_val = distance;
                s1 = words[i];
                s2 = words[j];
            }
        }
    }

    // Возвращаем пару, если таковая имеется
    if (s1.length() != 0)
        return "[" + s1 + " - " + s2 + "] - min: " + to_string(min_val);
    return "There're no matching pairs";
}

int main() {
    string line = "When we do search for a string in file, browser, or database, "
                   "pattern searching algorithms are used to show the results.";
    string line1 = "In computer science, the Boyer–Moore string-search algorithm is an efficient string-searching algorithm that is the standard benchmark for practical string-search literature.[1] It was developed by Robert S. Boyer and J Strother Moore in 1977.[2] The original paper contained static tables for computing the pattern shifts without an explanation of how to produce them. The algorithm for producing the tables was published in a follow-on paper; this paper contained errors which were later corrected by Wojciech Rytter in 1980.[3][4]\n"
                   "\n"
                   "The algorithm preprocesses the string being searched for (the pattern), but not the string being searched in (the text). It is thus well-suited for applications in which the pattern is much shorter than the text or where it persists across multiple searches. The Boyer–Moore algorithm uses information gathered during the preprocess step to skip sections of the text, resulting in a lower constant factor than many other string search algorithms. In general, the algorithm runs faster as the pattern length increases. The key features of the algorithm are to match on the tail of the pattern rather than the head, and to skip along the text in jumps of multiple characters rather than searching every single character in the text.";

    string pattern = "Boyer–Moore";

    BoyerMooreSearch bm;

    int task;
    cout << "Enter the number of task (1 or 2):";
    cin >> task;
    switch (task) {
        case 1:
            cout << get_min_distance_pairs(line) << endl;
            break;
        case 2:
            bm.turbo_search(pattern, line1);
            break;
        default:
            cout << "Incorrect input data!\n";
    }
    return 0;
}
