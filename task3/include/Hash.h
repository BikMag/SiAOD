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
    int size = 100;             // ������ ���-�������
    int count = 0;              // ���������� ����������� �����
    const float MIN_CAP = 0.7;  // ��������� �������� ��� ������������� �������
    vector<LinkedList> table;   // ���-�������, ���������� ������� ������

    public:
        Hash()
        {
            // ��������� ������� '�������' ����������
            LinkedList ll;
            vector<LinkedList> t(size, ll);
            table = t;

            // ��������� � ������� �������� �� ���������� ���������� �����
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

        // ������� ��� ������ �� ���-�������
        void print_table(bool printEmpty = true)
        {
            cout << "===============HASH_TABLE=================\n";
            for (int i = 0; i < table.size(); i++)
            {
                if (!table[i].is_empty() || printEmpty)
                    cout << setw(to_string(size-1).length()) << i << ": " << table[i].get_list() << '\n';
            }
        }

        // ���������� ������� �� ������� �� �����
        string get_val(int key)
        {
            int index;
            LinkedList* ll;

            // ����� � �������� ����������
            for (int i = 0; i < size; i++)
            {
                // ������������ ������
                index = hash_func(key) + i * hash_func2(key);

                // ���� ������ �� ������, ���� �� �������� ������ �������
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

        // �������� ���-�������
        int hash_func(int k)
        {
            return k % size;
        }

        // ������ ���-�������
        int hash_func2(int k)
        {
            return k % 7 + 1;
        }

        // ���������� ������
        void to_hash(int key, string fullName, string adress)
        {
            int index;
            // ����� � �������� ����������
            for (int i = 0; i < size; i++)
            {
                // ������������ ������
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

        // ������� ������� �� ������� �� �����
        void remove(int key)
        {
            int index;
            LinkedList* ll;
            LinkedList* llPrev;

            // ����� �������� �� �����
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
                            // �������� ���������� ��������
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

                    // �������� ����������� � �������� ��������� �� 1 ������� ������
                    llPrev = ll;
                    ll = ll->next;
                } while (ll != nullptr);
            }
            cout << "Element is not found\n";
        }

    private:
        // ������������ ������
        void rehash()
        {
            if ((float)count / size <= MIN_CAP)
                return;

            cout << "WARNING! The capacity of hash-table is over 70%. Rehashing the table...\n";

            // �������� ������� � �������� ����� �������
            count = 0;
            size *= 2;

            // ������� �������� ������� ������� � ������������ ������ � �����
            LinkedList llEmpty;
            vector<LinkedList> t = table;
            vector<LinkedList> newTable(size, llEmpty);
            table = newTable;

            // ���� ������� �� ������ ������� � ���������� � �����
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
