#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <Windows.h>
using namespace std;

// Выводит битовую последовательность из числа типа insigned char
void print_bin_char(unsigned char character) {
    cout << ' ' << bitset<8>(character) << endl;
}

// Отображает процесс установки бита в 0 или 1
void set_bit(unsigned int n, unsigned int position, bool bit) {
    unsigned char x = n;       // Число
    unsigned char maska = 1;   // Маска для замены бита (в дальнейшем он будет сдвигаться)
    unsigned char y;           // Результат

    print_bin_char(x);  // Выводим битовую последовательность для х

    // Меняем бит
    if (!bit) { // Для установки в 0
        y = x & (~(maska << position));
        cout << '&' << endl;
        print_bin_char(~(maska << position)); // Выводим маску
    }
    else { // Для установки в 1
        y = x | (maska << position);
        cout << '|' << endl;
        print_bin_char((maska << position));  // Выводим маску
    }

    cout << "---------" << endl;
    print_bin_char(y);  // Выводим битовую последовательность получившегося числа

    cout << "Result for " << (int)x << ": " << (int)y << endl;
}

// Код первого задания
void task1() {
    unsigned int n;         // Число
    unsigned int position;  // Номер бита для установки
    bool bit;               // Бит, который будет установлен

    cout << "Enter the number from 0 to 255: ";
    cin >> n;

    cout << "Enter the position you want to change: ";
    cin >> position;

    cout << "Enter the the value of bit (0 or 1): ";
    cin >> bit;

    set_bit(n, position, bit); // Устанавливаем бит в заданной позиции
}

// Код из файла
int listing1() {
    unsigned int x = 25;
    const int n = sizeof(int)*8; //=32 - кол-во разрядов в числе типа int
    unsigned maska = (1 << n - 1); //1 в старшем бите 32-разрядной сетки
    cout << "Начальный вид маски: " << bitset<n> (maska) << endl;
    cout << "Результат: ";
    for (int i = 1; i <= n; i++) { //32 раза - по кол-ву разрядов:
        cout << ((x & maska) >> (n - i));
        maska = maska >> 1; //смещение 1 в маске на разряд вправо
    }
    cout << endl;
    system("pause");
    return 0;
}

// Сортировка с помощью битовой последовательности
void task2_1() {
    int n, i = 0;               // переменная ввода и кол-во записанных чисел
    unsigned long long x = 0;   // последовательность для записи бит
    unsigned long long maska;   // маска
    unsigned int size = sizeof(unsigned long long)*8; //кол-во битов в unsigned long long

    cout << "Enter the different numbers from 0 to " << size - 1 << " (-1 to finish writing numbers): ";

    // Цикл ввода последовательности чисел
    do {
        cin >> n;

        if (n == -1) break; // Условие завершения ввода последовательности чисел

        maska = 1;

        x = x | (maska << size - n - 1); // Запись в битовую последовательность

        i++;
    } while (i < size); // Ограничение на количество вводимых чисел

    cout << "After sorting: " << endl;
    cout << ' ' << bitset<64>(x) << endl; // Выводим получившуюся последовательность

    maska = (1 << size - 1);

    // Цикл вывода набора отсортированных чисел
    for (int i = 1; i <= size; i++) {
        // Если в бите 1 - выводим число
        if (((x & maska) >> (size - i)) == 1)
            cout << i - 1 << ' ';
        maska = maska >> 1; //смещение 1 в маске на разряд вправо
    }
    cout << endl;
}

// Сортировка с помощью битового массива (вектора)
void task2_2() {
    int n, i = 0;             // переменная ввода и кол-во записанных чисел
    vector<unsigned char> x;  // битовый массив
    unsigned char maska;      // маска
    unsigned int size_ = sizeof(unsigned char)*8; //кол-во битов в unsigned char


    cout << "Enter the different non-negative numbers (-1 to finish writing numbers): ";

    // Цикл ввода последовательности чисел
    do {
        cin >> n;

        if (n == -1) break; // Условие завершения ввода последовательности чисел

        unsigned int vec_size = x.size(); // Размер вектора в байтах
        // Если число не влезает в вектор, создаётся доп. пространство в сетке
        if (n / 8 + 1 > x.size()) {
            // Из минимально возможного размера вектора вычитаем текущий
            for (int i = 0; i < n/8 - vec_size + 1; i++)
                x.push_back(0); // Добавляем разницу
        }

        maska = 1;
        // Запись в битовый массив
        x[n/8] = x[n/8] | (maska << size_ - (n%8) - 1);

        i++;
    } while (n != -1); // Условие завершения ввода последовательности чисел

    cout << "After sorting: " << endl;
    for (int i = 0; i < x.size(); i++) {
        cout << bitset<8>(x[i]) << ' ';
    }
    cout << endl;

    // Цикл вывода набора отсортированных чисел
    // Работает аналогично с предыдущим + смещение по разрядам
    for (int i = 0; i < x.size(); i++) {
        maska = (1 << size_ - 1);

        for (int j = 1; j <= size_; j++) {
            if (((x[i] & maska) >> (size_ - j)) == 1)
                cout << (j-1) + 8*i << ' ';
            maska = maska >> 1;
        }
    }

    cout << endl;
}

// Быстрая сортировка числового файла с помощью битового массива
void task3() {
    string file_name = "files/testBIG.txt";  // Имя файла
    ifstream fin(file_name);        // Входной файл
    ofstream fout("files/res.txt");       // Выходной файл
    string str;                     // Строка для получения числа из файла

    vector<unsigned char> x;        // битовый массив
    unsigned char maska;            // маска
    unsigned int size_ = sizeof(unsigned char)*8; //кол-во битов в unsigned char
    int n, i = 0;   // переменная ввода и кол-во записанных чисел

    cout << "Taking numbers from file '" << file_name << "'";

    if (!fin.is_open()) { // Если файла нет, останавливаем работу программы
        cout << "ReadingFileError(" << file_name << ")" << endl;
        return;
    }

    int start = clock(); // Начало отсчета работы программы

    // Цикл чтения данных из файла и их обработка
    while(!fin.eof()) {
        getline(fin, str); // Берем число из файла
        //cout << str << ' ';
        n = stoi(str);  // Приводим к типу int


        if (n == -1) break; // Условие завершения ввода последовательности чисел

        unsigned int vec_size = x.size(); // Размер вектора в байтах
        // Если число не влезает в вектор, создаётся доп. пространство в сетке
        if (n / 8 + 1 > x.size()) {
            for (int i = 0; i < n/8 - vec_size + 1; i++)
                x.push_back(0);
        }

        maska = 1;
        // Запись в битовый массив
        x[n/8] = x[n/8] | (maska << size_ - (n%8) - 1);
    }

    fin.close(); // Закрываем входной файл

    cout << endl;

    cout << "After sorting: " << endl;
    // Выводим побитово получившуюся последовательность
    if (x.size() <= 8) {
        for (int i = 0; i < x.size(); i++) {
            cout << bitset<8>(x[i]) << ' ';
        }
        cout << endl;
    }
    else // Если не влезает в консоль, выводим соответствующее сообщение
        cout << "Many bits" << endl;

    // Цикл вывода в файл набора отсортированных чисел
    for (int i = 0; i < x.size(); i++) {
        maska = (1 << size_ - 1);

        for (int j = 1; j <= size_; j++) {
            if (((x[i] & maska) >> (size_ - j)) == 1)
                fout << (j-1) + 8*i << '\n';
            maska = maska >> 1;
        }
    }

    int finish = clock(); // Конец отсчета работы программы

    int fin_size = x.size(); // Итоговый размер вектора в байтах

    // Отображение битового массива в байтах/килобайтах/мегабайтах
    cout << "Size of bit array: ";
    if (fin_size < 1024)
        cout << fin_size << " B" << endl;
    else if (fin_size >= 1024 && fin_size < 1024*1024)
        cout << fin_size / 1024.0 << " KB" << endl;
    else if (fin_size >= 1024*1024)
        cout << fin_size / (1024*1024.0) << " MB" << endl;

    // Отображение времени работы программы
    cout << "Time: " << static_cast<float>(finish - start)/CLOCKS_PER_SEC << " s" << endl;

}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Интерфейс для перехода между заданиями
    int task_num, part;
    do {
        cout << "Choose number of task (-1 to quit): ";
        cin >> task_num;

        switch(task_num) {
        case 1:
            cout << "Example (0) or listing(1): ";
            cin >> part;

            if (part == 0) task1();
            else listing1();

            break;
        case 2:
            cout << "Array (0) or vector(1): ";
            cin >> part;

            if (part == 0) task2_1();
            else task2_2();
            break;
        case 3:
            task3();
            break;
        }
        cout << "====================" << endl;
    } while (task_num != -1);

    return 0;
}
