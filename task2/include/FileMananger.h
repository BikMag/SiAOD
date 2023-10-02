#ifndef FILEMANANGER_H
#define FILEMANANGER_H

#include <vector>
#include <iomanip>
#include <ctime>
#include <string>

// Класс с полями и методами для работы с файлами
class FileMananger
{
    private:
        const int LENGTH = 45;                  // Фиксированная длина строки в файле
        const int POLIS_SIZE = 16;              // Число знаков в номере полиса
        vector<vector<string>> pointer_table;   // Таблица с ключами и ссылками

    public:
        int tableSize = 0;

        // Имена текстового и двоичного файлов
        const string BINFILE = "binfile.bin";
        const string TEXTFILE = "test.txt";

        // Создание файла
        void create_rand_file(int count, string new_file)
        {
            // Очищаем таблицу при повторном создании
            pointer_table.clear();

            ofstream fout(new_file);

            // Форматируем вывод в файл
            fout << setw(16) << "POLIS_ID" << ' '
                     << setw(12) << "COMPANY" << ' '
                     << setw(15) << "SECOND_NAME" << '\n';


            long long polis = 1000000000000000;

            // Записываем данные случайным образом
            srand(time(0));
            for (int i = 0; i < count; i++)
            {
                polis += rand() % 9999 + 1;
                fout << setw(POLIS_SIZE) << polis << ' '
                     << setw(12) << "comp#" + to_string(rand() % 1000) << ' '
                     << setw(15) << "sec#" + to_string(rand() % 1000) <<'\n';
            }

            fout.close();
        }

        // Перевод файла в двоичный формат
        void write_to_binary(string fname, string fbname)
        {
            ifstream pTextFile(fname, ios::in);
            ofstream pBinaryFile(fbname, ios::out|ios::binary);

            // Если файл не удалось открыть
            if (!pTextFile.is_open())
            {
                printf("File '%s' doesn't exist\n", fname.c_str());
                return;
            }

            string str;

            // Читаем текстовый файл по строкам и записываем их в двоичный файл
            while (!pTextFile.eof())
            {
                getline(pTextFile, str);
                pBinaryFile.write(&str[0], str.size());
            }

            pTextFile.close();
            pBinaryFile.close();

            printf("Converting to binary was completed\n");
        }

        // Чтение двоичного файла и запись в таблицу
        void read_from_binary(string fbname)
        {
            ifstream pBinaryFile(fbname, ios::in|ios::binary);

            // Если файл не удалось открыть
            if (!pBinaryFile.is_open())
            {
                printf("File '%s' doesn't exist\n", fbname.c_str());
                return;
            }

            // Создаем буфер для хранения данных из файла
            char buffer[LENGTH];
            int idx = 0;

            while (!pBinaryFile.eof())
            {
                // Получаем строку из файла
                pBinaryFile.read(buffer, LENGTH);

                // Не записываем в таблицу первую строку с информацией о столбцах
                if (idx == 0)
                {
                    idx++;
                    continue;
                }

                stringstream ss(buffer);
                string s;

                vector<string> line;

                // Разбираем строку по составляющим, чтобы вытащить ключ
                for (int i = 0; i < 3; i++)
                {
                    getline(ss, s, ' ');
                    if (i == 0)
                        line.push_back(s);
                }

                // Добавляем ссылку со смещением
                line.push_back(to_string(idx * LENGTH));

                // Записываем полученную строку в файл
                pointer_table.push_back(line);

                idx++;
            }

            // Удаляем дупликат в конце
            pointer_table.pop_back();

            // Сохраняем информацию о размере таблицы
            this->tableSize = pointer_table.size();

            pBinaryFile.close();
        }

        // Вывод из строк из файла по ключам в таблице
        void print_table()
        {
            for (int i = 0; i < pointer_table.size() + 1; i++)
            {
                read_line(BINFILE, i);
            }
        }

        // Вывод таблицы с ключами и ссылками
        void print_pointer_table()
        {

            for (int i = 0; i < pointer_table.size(); i++)
            {
                cout << setw(16) << pointer_table[i][0] << ' '
                     << setw(6) << pointer_table[i][1] << '\n';
            }
        }

        // Получить строку из файла через позицию
        void read_line(string fbname, int num)
        {
            // Проверяем правильность введенного номера строки
            if (num < 0 || num > pointer_table.size())
            {
                printf("Input error\n");
                return;
            }

            ifstream pBinaryFile(fbname, ios::in|ios::binary);

            // Если файл не удалось открыть
            if (!pBinaryFile.is_open())
            {
                printf("File '%s' doesn't exist\n", fbname.c_str());
                return;
            }

            char buffer[LENGTH] = "";

            // Пропускаем содержимое в начале файла
            for (int i = 0; i < num; i++)
                pBinaryFile.read(buffer, LENGTH);

            // Записываем след. строку
            pBinaryFile.read(buffer, LENGTH);
            cout << buffer << '\n';

            pBinaryFile.close();
        }

        // Получить таблицу
        vector<vector<string>> get_table()
        {
            return pointer_table;
        }

        // Получить значение ключа
        string get_key(int i)
        {
            return pointer_table[i][0];
        }
};

#endif // FILEMANANGER_H
