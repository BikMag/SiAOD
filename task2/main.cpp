#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <ctime>
#include <Windows.h>
using namespace std;

#include "FileMananger.h"

int iterations; // ���������� �������� �������� � ���������

// �������� �����
void linear_search(FileMananger fm, string key)
{
    iterations = 0;

    vector<vector<string>> table = fm.get_table();
    string s;

    int i = 1;

    // ������������� ������� �� ������ �� �����, ���� �� �������� ������ �������
    for (auto line: table)
    {
        iterations++;

        // ���� ������� ������
        if (line[0] == key)
        {
            iterations++;

            // ������� ������ �� ����� �� �����
            fm.read_line(fm.BINFILE, i);
            return;
        }
        i++;
    }
    // ���� ������� �� ������
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

// ����� ���������
void fibonacci_search(FileMananger fm, string key)
{
    iterations = 0;

    int len = fm.tableSize; // ���-�� ����� �������

    int start = -1; // ������ �������

    // ������ ����� ���������
    int f0 = 0;
    int f1 = 1;
    int f2 = 1;

    // ���� �����, ������� ��� ������ len
    while(f2 < len)
    {
        iterations++;
        f0 = f1;
        f1 = f2;
        f2 = f1 + f0;
    }

    int index; // ������ ���������� ����� � �������

    // ���� f2 = 0 - ���� ���������������
    while (f2 > 1)
    {
        iterations++;

        // ������ ������, ����������� �������� ����� �� 2 �����
        index = min(start + f0, len - 1);

        // ���������� ������� �� ��������� �� �������
        if (fm.get_key(index) < key)
        {
            iterations++;

            // �������� ����� �� 1 ������� ���� �� ������ ����� ���������
            f2 = f1;
            f1 = f0;
            f0 = f2 - f1;

            // ������� ����� �������
            start = index;

        }
        else if (fm.get_key(index) > key)
        {
            iterations += 2;

            // �������� ����� �� 2 ������� ���� �� ������ ����� ���������
            f2 = f0;
            f1 = f1 - f0;
            f0 = f2 - f1;
        }
        else
        {
            iterations += 2;

            // ������� ������ �� ���������� ��������
            fm.read_line(fm.BINFILE, index + 1);
            return;
        }
    }
    iterations++;

    // ���������� � ��������� ���������
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

    // ��������� ��� �������� ����� ���������
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
