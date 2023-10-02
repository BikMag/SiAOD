#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <ctime>
#include <Windows.h>
using namespace std;

#include "FileMananger.h"

int iterations; // Переменная подсчета итераций и сравнений

// Линейный поиск
void linear_search(FileMananger fm, string key)
{
    iterations = 0;

    vector<vector<string>> table = fm.get_table();
    string s;

    int i = 1;

    // Просматриваем таблицу от начала до конца, пока не найдется нужный элемент
    for (auto line: table)
    {
        iterations++;

        // Если элемент найден
        if (line[0] == key)
        {
            iterations++;

            // Выводим данные из файла по ключу
            fm.read_line(fm.BINFILE, i);
            return;
        }
        i++;
    }
    // Если элемент не найден
    cout << "Not found\n";
}


void bin_search(FileMananger fm, string key)
{
    iterations = 0;

    int left = 0, right = fm.tableSize;
    int mid;
    string keyFromTable;

    while (right - left > 1)
    {
        iterations++;
        mid = (left + right) / 2;
        keyFromTable = fm.get_key(mid);

        if (key < keyFromTable)
            right = mid;
        else if (key > keyFromTable)
            left = mid;
        else if (key == keyFromTable)
        {
            fm.read_line(fm.BINFILE, mid + 1);
            return;
        }
    }

    cout << "Not found\n";
}

// Поиск Фибоначчи
void fibonacci_search(FileMananger fm, string key)
{
    iterations = 0;

    int len = fm.tableSize; // Кол-во строк таблицы

    int start = -1; // Начало отсчета

    // Тройка чисел Фибоначчи
    int f0 = 0;
    int f1 = 1;
    int f2 = 1;

    // Ищем число, большее или равное len
    while(f2 < len)
    {
        iterations++;
        f0 = f1;
        f1 = f2;
        f2 = f1 + f0;
    }

    int index; // Индекс найденного числа в таблице

    // Если f2 = 0 - цикл останавливается
    while (f2 > 1)
    {
        iterations++;

        // Задаем индекс, разделяющий заданный набор на 2 части
        index = min(start + f0, len - 1);

        // Сравниваем элемент со значением из таблицы
        if (fm.get_key(index) < key)
        {
            iterations++;

            // Смещение чисел на 1 позицию вниз по набору чисел Фибоначчи
            f2 = f1;
            f1 = f0;
            f0 = f2 - f1;

            // Задание левой границы
            start = index;

        }
        else if (fm.get_key(index) > key)
        {
            iterations += 2;

            // Смещение чисел на 2 позиции вниз по набору чисел Фибоначчи
            f2 = f0;
            f1 = f1 - f0;
            f0 = f2 - f1;
        }
        else
        {
            iterations += 2;

            // Выводим запись по найденному элементу
            fm.read_line(fm.BINFILE, index + 1);
            return;
        }
    }
    iterations++;

    // Сравниваем с последним элементом
    if (f1 && fm.get_key(len - 1) == key)
        fm.read_line(fm.BINFILE, len);
    else
        cout << "Not found\n";
}


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    FileMananger fm;

    // Интерфейс для перехода между заданиями
    int task_num;
    int length;
    int start, finish;
    bool is_agree;
    string polisID;
    do {
        cout << "Choose number of task [1-3] (-1 to quit): ";
        cin >> task_num;

        switch(task_num) {
        case 1:
            cout << "---CREATING THE BINARY FILE---\n";

            cout << "Enter the length of file: ";
            cin >> length;

            if (length <= 0)
            {
                cout << "Incorrect size of file (the length must be positive number)\n";
                break;
            }

            fm.create_rand_file(length, fm.TEXTFILE);
            fm.write_to_binary(fm.TEXTFILE, fm.BINFILE);
            fm.read_from_binary(fm.BINFILE);

            cout << "Print table of pointers? ";
            cin >> is_agree;
            if (is_agree) fm.print_pointer_table();

            cout << "Print table of values? ";
            cin >> is_agree;
            if (is_agree) fm.print_table();

            break;
        case 2:
            cout << "---LINEAR SEARCH---\n";

            if (fm.tableSize == 0)
            {
                cout << "The table is empty. Enter '1' to begin\n";
                break;
            }

            cout << "Enter the polis ID: ";
            cin >> polisID;

            start = clock();
            linear_search(fm, polisID);
            finish = clock();

            cout << "Time: " << static_cast<float>(finish - start)/CLOCKS_PER_SEC << " s" << endl;
            cout << "Iterations: " << iterations << endl;

            break;
        case 3:
            cout << "---FIBONACCI SEARCH---\n";

            if (fm.tableSize == 0)
            {
                cout << "The table is empty. Enter '1' to begin\n";
                break;
            }

            cout << "Enter the polis ID: ";
            cin >> polisID;

            start = clock();
            fibonacci_search(fm, polisID);
            finish = clock();

            cout << "Time: " << static_cast<float>(finish - start)/CLOCKS_PER_SEC << " s" << endl;
            cout << "Iterations: " << iterations << endl;
        }

        cout << "====================" << endl;
    } while (task_num != -1);

    return 0;
}
