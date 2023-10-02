#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
using namespace std;

#include "LinkedList.h"

class Hash
{
    int size = 100;             // Размер хеш-таблицы
    int count = 0;              // Количество заполненных ячеек
    const float MIN_CAP = 0.7;  // Пороговое значение для рехеширования таблицы
    vector<LinkedList> table;   // Хеш-таблица, содержащая связные списки

    public:
        Hash()
        {
            // Заполняем таблицу 'пустыми' элементами
            LinkedList ll;
            vector<LinkedList> t(size, ll);
            table = t;

            // Добавляем в таблицу элементы со случайными значениями полей
            srand(0);
            int r;
            string s1, s2;
            for (int i = 0; i < 70; i++)
            {
                r = rand() % 90000 + 10000;
                s1 = "Name" + to_string(i);
                s2 = "adress" + to_string(i);
                to_hash(r, s1, s2);
            }
        }

        // Выводит все данные из хеш-таблицы
        void print_table(bool printEmpty = true)
        {
            cout << "===============HASH_TABLE=================\n";
            for (int i = 0; i < table.size(); i++)
            {
                if (!table[i].is_empty() || printEmpty)
                    cout << setw(to_string(size-1).length()) << i << ": " << table[i].get_list() << '\n';
            }
        }

        // Возвращает элемент из таблицы по ключу
        string get_val(int key)
        {
            int index;
            LinkedList* ll;

            // Поиск с открытой адресацией
            for (int i = 0; i < size; i++)
            {
                // Хешированный индекс
                index = hash_func(key) + i * hash_func2(key);

                // Берём индекс по модулю, если он превысил размер таблицы
                if (index >= size)
                    index %= size;

                ll = &table[index];
                if (ll->is_empty())
                    break;

                do
                {
                    if (ll->id == key)
                        return ll->get();
                    ll = ll->next;
                } while (ll != nullptr);
            }
            return "none";
        }

        // Основная хеш-функция
        int hash_func(int k)
        {
            return k % size;
        }

        // Вторая хеш-функция
        int hash_func2(int k)
        {
            return k % 7 + 1;
        }

        // Хешировать данные
        void to_hash(int key, string fullName, string adress)
        {
            int index;
            // Поиск с открытой адресацией
            for (int i = 0; i < size; i++)
            {
                // Хешированный индекс
                index = hash_func(key) + i * hash_func2(key);

                if (index >= size)
                    index %= size;

                if (table[index].is_empty())
                {
                    table[index].set(key, fullName, adress);
                    count++;
                    rehash();
                    return;
                }
            }
            table[hash_func(key)].set(key, fullName, adress);
            count++;
            rehash();
        }

        // Удалить элемент из таблицы по ключу
        void remove(int key)
        {
            int index;
            LinkedList* ll;
            LinkedList* llPrev;

            // Поиск элемента по ключу
            for (int i = 0; i < size; i++)
            {
                index = hash_func(key) + i * hash_func2(key);

                if (index >= size)
                    index %= size;

                ll = &table[index];
                if (ll->is_empty())
                    break;

                llPrev = nullptr;

                do
                {
                    if (ll->id == key)
                    {
                        if (llPrev == nullptr)
                        {
                            // Удаление найденного элемента
                            if (ll->next == nullptr)
                            {
                                LinkedList llNew;
                                table[index] = llNew;
                            }
                            else
                                table[index] = *ll->next;
                        }
                        else
                            llPrev->next = ll->next;

                        count--;
                        cout << "Element has found and removed\n";
                        return;
                    }

                    // Смещение предыдущего и текущего элементов на 1 позицию вправо
                    llPrev = ll;
                    ll = ll->next;
                } while (ll != nullptr);
            }
            cout << "Element is not found\n";
        }

    private:
        // Рехешировать данные
        void rehash()
        {
            if ((float)count / size <= MIN_CAP)
                return;

            cout << "WARNING! The capacity of hash-table is over 70%. Rehashing the table...\n";

            // Обнуляем счетчик и удаиваем разер таблицы
            count = 0;
            size *= 2;

            // Создаем дубликат текущей таблицы и переписываем данные в новую
            LinkedList llEmpty;
            vector<LinkedList> t = table;
            vector<LinkedList> newTable(size, llEmpty);
            table = newTable;

            // Берём элемент из старой таблицы и записываем в новую
            for (LinkedList llCur: t)
            {
                LinkedList* ll = &llCur;
                while (ll != nullptr)
                {
                    if (!ll->is_empty())
                        to_hash(ll->id, ll->fullName, ll->adress);

                    ll = ll->next;
                }
            }

            cout << "Rehashing complete\n";
        }
};

#endif // HASH_H
