#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <Windows.h>
using namespace std;

// ������� ������� ������������������ �� ����� ���� insigned char
void print_bin_char(unsigned char character) {
    cout << ' ' << bitset<8>(character) << endl;
}

// ���������� ������� ��������� ���� � 0 ��� 1
void set_bit(unsigned int n, unsigned int position, bool bit) {
    unsigned char x = n;       // �����
    unsigned char maska = 1;   // ����� ��� ������ ���� (� ���������� �� ����� ����������)
    unsigned char y;           // ���������

    print_bin_char(x);  // ������� ������� ������������������ ��� �

    // ������ ���
    if (!bit) { // ��� ��������� � 0
        y = x & (~(maska << position));
        cout << '&' << endl;
        print_bin_char(~(maska << position)); // ������� �����
    }
    else { // ��� ��������� � 1
        y = x | (maska << position);
        cout << '|' << endl;
        print_bin_char((maska << position));  // ������� �����
    }

    cout << "---------" << endl;
    print_bin_char(y);  // ������� ������� ������������������ ������������� �����

    cout << "Result for " << (int)x << ": " << (int)y << endl;
}

// ��� ������� �������
void task1() {
    unsigned int n;         // �����
    unsigned int position;  // ����� ���� ��� ���������
    bool bit;               // ���, ������� ����� ����������

    cout << "Enter the number from 0 to 255: ";
    cin >> n;

    cout << "Enter the position you want to change: ";
    cin >> position;

    cout << "Enter the the value of bit (0 or 1): ";
    cin >> bit;

    set_bit(n, position, bit); // ������������� ��� � �������� �������
}

// ��� �� �����
int listing1() {
    unsigned int x = 25;
    const int n = sizeof(int)*8; //=32 - ���-�� �������� � ����� ���� int
    unsigned maska = (1 << n - 1); //1 � ������� ���� 32-��������� �����
    cout << "��������� ��� �����: " << bitset<n> (maska) << endl;
    cout << "���������: ";
    for (int i = 1; i <= n; i++) { //32 ���� - �� ���-�� ��������:
        cout << ((x & maska) >> (n - i));
        maska = maska >> 1; //�������� 1 � ����� �� ������ ������
    }
    cout << endl;
    system("pause");
    return 0;
}

// ���������� � ������� ������� ������������������
void task2_1() {
    int n, i = 0;               // ���������� ����� � ���-�� ���������� �����
    unsigned long long x = 0;   // ������������������ ��� ������ ���
    unsigned long long maska;   // �����
    unsigned int size = sizeof(unsigned long long)*8; //���-�� ����� � unsigned long long

    cout << "Enter the different numbers from 0 to " << size - 1 << " (-1 to finish writing numbers): ";

    // ���� ����� ������������������ �����
    do {
        cin >> n;

        if (n == -1) break; // ������� ���������� ����� ������������������ �����

        maska = 1;

        x = x | (maska << size - n - 1); // ������ � ������� ������������������

        i++;
    } while (i < size); // ����������� �� ���������� �������� �����

    cout << "After sorting: " << endl;
    cout << ' ' << bitset<64>(x) << endl; // ������� ������������ ������������������

    maska = (1 << size - 1);

    // ���� ������ ������ ��������������� �����
    for (int i = 1; i <= size; i++) {
        // ���� � ���� 1 - ������� �����
        if (((x & maska) >> (size - i)) == 1)
            cout << i - 1 << ' ';
        maska = maska >> 1; //�������� 1 � ����� �� ������ ������
    }
    cout << endl;
}

// ���������� � ������� �������� ������� (�������)
void task2_2() {
    int n, i = 0;             // ���������� ����� � ���-�� ���������� �����
    vector<unsigned char> x;  // ������� ������
    unsigned char maska;      // �����
    unsigned int size_ = sizeof(unsigned char)*8; //���-�� ����� � unsigned char


    cout << "Enter the different non-negative numbers (-1 to finish writing numbers): ";

    // ���� ����� ������������������ �����
    do {
        cin >> n;

        if (n == -1) break; // ������� ���������� ����� ������������������ �����

        unsigned int vec_size = x.size(); // ������ ������� � ������
        // ���� ����� �� ������� � ������, �������� ���. ������������ � �����
        if (n / 8 + 1 > x.size()) {
            // �� ���������� ���������� ������� ������� �������� �������
            for (int i = 0; i < n/8 - vec_size + 1; i++)
                x.push_back(0); // ��������� �������
        }

        maska = 1;
        // ������ � ������� ������
        x[n/8] = x[n/8] | (maska << size_ - (n%8) - 1);

        i++;
    } while (n != -1); // ������� ���������� ����� ������������������ �����

    cout << "After sorting: " << endl;
    for (int i = 0; i < x.size(); i++) {
        cout << bitset<8>(x[i]) << ' ';
    }
    cout << endl;

    // ���� ������ ������ ��������������� �����
    // �������� ���������� � ���������� + �������� �� ��������
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

// ������� ���������� ��������� ����� � ������� �������� �������
void task3() {
    string file_name = "files/testBIG.txt";  // ��� �����
    ifstream fin(file_name);        // ������� ����
    ofstream fout("files/res.txt");       // �������� ����
    string str;                     // ������ ��� ��������� ����� �� �����

    vector<unsigned char> x;        // ������� ������
    unsigned char maska;            // �����
    unsigned int size_ = sizeof(unsigned char)*8; //���-�� ����� � unsigned char
    int n, i = 0;   // ���������� ����� � ���-�� ���������� �����

    cout << "Taking numbers from file '" << file_name << "'";

    if (!fin.is_open()) { // ���� ����� ���, ������������� ������ ���������
        cout << "ReadingFileError(" << file_name << ")" << endl;
        return;
    }

    int start = clock(); // ������ ������� ������ ���������

    // ���� ������ ������ �� ����� � �� ���������
    while(!fin.eof()) {
        getline(fin, str); // ����� ����� �� �����
        //cout << str << ' ';
        n = stoi(str);  // �������� � ���� int


        if (n == -1) break; // ������� ���������� ����� ������������������ �����

        unsigned int vec_size = x.size(); // ������ ������� � ������
        // ���� ����� �� ������� � ������, �������� ���. ������������ � �����
        if (n / 8 + 1 > x.size()) {
            for (int i = 0; i < n/8 - vec_size + 1; i++)
                x.push_back(0);
        }

        maska = 1;
        // ������ � ������� ������
        x[n/8] = x[n/8] | (maska << size_ - (n%8) - 1);
    }

    fin.close(); // ��������� ������� ����

    cout << endl;

    cout << "After sorting: " << endl;
    // ������� �������� ������������ ������������������
    if (x.size() <= 8) {
        for (int i = 0; i < x.size(); i++) {
            cout << bitset<8>(x[i]) << ' ';
        }
        cout << endl;
    }
    else // ���� �� ������� � �������, ������� ��������������� ���������
        cout << "Many bits" << endl;

    // ���� ������ � ���� ������ ��������������� �����
    for (int i = 0; i < x.size(); i++) {
        maska = (1 << size_ - 1);

        for (int j = 1; j <= size_; j++) {
            if (((x[i] & maska) >> (size_ - j)) == 1)
                fout << (j-1) + 8*i << '\n';
            maska = maska >> 1;
        }
    }

    int finish = clock(); // ����� ������� ������ ���������

    int fin_size = x.size(); // �������� ������ ������� � ������

    // ����������� �������� ������� � ������/����������/����������
    cout << "Size of bit array: ";
    if (fin_size < 1024)
        cout << fin_size << " B" << endl;
    else if (fin_size >= 1024 && fin_size < 1024*1024)
        cout << fin_size / 1024.0 << " KB" << endl;
    else if (fin_size >= 1024*1024)
        cout << fin_size / (1024*1024.0) << " MB" << endl;

    // ����������� ������� ������ ���������
    cout << "Time: " << static_cast<float>(finish - start)/CLOCKS_PER_SEC << " s" << endl;

}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // ��������� ��� �������� ����� ���������
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
