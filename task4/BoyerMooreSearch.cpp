#include <iostream>
#include <vector>
#include <iomanip>

#include "BoyerMooreSearch.h"

using namespace std;

// Построение таблицы стоп-символов для шаблона pattern
void BoyerMooreSearch::fill_symbol_table(string pattern) {
    int size = pattern.length();
    vector<int> badchar(128, -1); // Таблица стоп-сиволов, -1 для отсутствующих символов

    // Заполнение индексами
    // Сохранение индекса последнего символа
    for (int i = 0; i < size - 1; i++) // Исключая последний символ
        badchar[(int)pattern[i]] = i;

    symbol_table = badchar; // Сохраняем таблицу в поле объекта
}

// Построение таблицы суффиксов на основе Z-функции
void BoyerMooreSearch::fill_suffix_table(std::string pattern) {
    int m = pattern.length();
    vector<int> suffshift(m + 1, m);

    // Вычисление Z-функции
    vector<int> z(m, 0);
    for (int j = 1, maxZidx = 0, maxZ = 0; j < m; ++j) {
        if (j <= maxZ)
            z[j] = min(maxZ - j + 1, (int)z[j - maxZidx]);
        while (j + z[j] < m
               && pattern[m - 1 - z[j]] == pattern[m - 1 - (j + z[j])])
            z[j]++;
        if (j + z[j] - 1 > maxZ) {
            maxZidx = j;
            maxZ = j + z[j] - 1;
        }
    }

    // Формирование таблицы суффиксов
    for (int j = m - 1; j > 0; j--)
        suffshift[m - z[j]] = j;
    for (int j = 1, r = 0; j <= m - 1; j++)
        if (j + z[j] == m)
            for (; r <= j; r++)
                if (suffshift[r] == m) suffshift[r] = j;

    suffix_table = suffshift; // Сохраняем таблицу в поле объекта
}

// Визуализация смещений шаблона вдоль строки
void print_steps(string line, string pattern, int shift, int step) {
    printf("Step %d:\n", step++);
    cout << line << endl;
    cout << setw(shift + pattern.length()) << pattern << "\n\n";
}

void BoyerMooreSearch::search(string pattern, string line) {
    fill_symbol_table(pattern);
    fill_suffix_table(pattern);

    vector<int> answer;

    int step = 0;
    for (int shift = 0; shift <= line.length() - pattern.length();) {

        step++;
//        print_steps(line, pattern, shift, step);

        int pos = pattern.length() - 1;
        while (pattern[pos] == line[pos + shift]) {
            if (pos == 0)
                answer.push_back(shift);
            --pos;
        }
        shift += max(suffix_table[pos + 1], pos - symbol_table[line[pos + shift]]);
    }
    if (answer.empty())
        cout << "There's no substring!\n";
    else {
        cout << "Indexes: ";
        for (int ans : answer)
            cout << ans << ' ';
        cout << endl;
    }
    cout << "Steps: " << step << endl;
}

// Поиск Боёера-Мура с турбосдвигом
void BoyerMooreSearch::turbo_search(std::string pattern, std::string line) {
    // Создаем таблицы символов и суффиксов
    fill_symbol_table(pattern);
    fill_suffix_table(pattern);

    int patt_len = pattern.length();
    int line_len = line.length();

    int i = 0;
    int u = 0;
    int shift = patt_len; // Величина сдвига во для последующей итерации

    // Вектор для хранения индексов смещения найденных слов
    vector<int> answer;

    if (patt_len == 0) return; // При отсутствии шаблона завершаем поиск

    int step = 0; // Кол-во смещений
    while (i <= line_len - patt_len) {

        step++;
//        print_steps(line, pattern, i, step);

        int j = patt_len - 1;
        while (j >= 0 and pattern[j] == line[i + j]) {
            j--;
            if (u != 0 and j == patt_len - 1 - shift)
                j -= u;
        }
        if (j < 0) { // При совпадении шаблона с подстрокой
            answer.push_back(i);
            shift = suffix_table[0];
            u = patt_len - shift;
        }
        else {
            int v = patt_len - 1 - j;
            int turboShift = u - v; // Использование турбосдвига

            int bCShift = symbol_table[line[i + j]] - patt_len + j + 1;

            shift = max(turboShift, max(bCShift, suffix_table[j + 1]));
            if (shift == suffix_table[j + 1])
                u = min(patt_len - shift, v);
            else {
                if (turboShift < bCShift)
                    shift = min(shift, u + 1);
                u = 0;
            }
        }
        i += shift; // Сдвиг шаблона
    }

    // Вывод найденных индексов
    if (answer.empty())
        cout << "There's no substring!\n";
    else {
        cout << "Indexes: ";
        for (int ans : answer)
            cout << ans << ' ';
        cout << endl;
    }
    cout << "Steps: " << step << endl;
}

// Отображение таблицы стоп-символов
void BoyerMooreSearch::print_symbol_table() {
    char ch;
    for (int i = 0; i < symbol_table.size(); i++) {
        if (symbol_table[i] != -1) {
            ch = i;
            cout << ch << ": " << symbol_table[i] << endl;
        }
    }
    printf("Others: %d\n", -1);
}

// Отображение таблицы суффиксов
void BoyerMooreSearch::print_suffix_table() {
    for (int i = 0; i < suffix_table.size(); i++) {
        cout << suffix_table[i] << endl;
    }
}



