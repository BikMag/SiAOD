#ifndef FILEMANANGER_H
#define FILEMANANGER_H

#include <vector>
#include <iomanip>
#include <ctime>
#include <string>

// ����� � ������ � �������� ��� ������ � �������
class FileMananger
{
    private:
        const int LENGTH = 45;                  // ������������� ����� ������ � �����
        const int POLIS_SIZE = 16;              // ����� ������ � ������ ������
        vector<vector<string>> pointer_table;   // ������� � ������� � ��������

    public:
        int tableSize = 0;

        // ����� ���������� � ��������� ������
        const string BINFILE = "binfile.bin";
        const string TEXTFILE = "test.txt";

        // �������� �����
        void create_rand_file(int count, string new_file)
        {
            // ������� ������� ��� ��������� ��������
            pointer_table.clear();

            ofstream fout(new_file);

            // ����������� ����� � ����
            fout << setw(16) << "POLIS_ID" << ' '
                     << setw(12) << "COMPANY" << ' '
                     << setw(15) << "SECOND_NAME" << '\n';


            long long polis = 1000000000000000;

            // ���������� ������ ��������� �������
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

        // ������� ����� � �������� ������
        void write_to_binary(string fname, string fbname)
        {
            ifstream pTextFile(fname, ios::in);
            ofstream pBinaryFile(fbname, ios::out|ios::binary);

            // ���� ���� �� ������� �������
            if (!pTextFile.is_open())
            {
                printf("File '%s' doesn't exist\n", fname.c_str());
                return;
            }

            string str;

            // ������ ��������� ���� �� ������� � ���������� �� � �������� ����
            while (!pTextFile.eof())
            {
                getline(pTextFile, str);
                pBinaryFile.write(&str[0], str.size());
            }

            pTextFile.close();
            pBinaryFile.close();

            printf("Converting to binary was completed\n");
        }

        // ������ ��������� ����� � ������ � �������
        void read_from_binary(string fbname)
        {
            ifstream pBinaryFile(fbname, ios::in|ios::binary);

            // ���� ���� �� ������� �������
            if (!pBinaryFile.is_open())
            {
                printf("File '%s' doesn't exist\n", fbname.c_str());
                return;
            }

            // ������� ����� ��� �������� ������ �� �����
            char buffer[LENGTH];
            int idx = 0;

            while (!pBinaryFile.eof())
            {
                // �������� ������ �� �����
                pBinaryFile.read(buffer, LENGTH);

                // �� ���������� � ������� ������ ������ � ����������� � ��������
                if (idx == 0)
                {
                    idx++;
                    continue;
                }

                stringstream ss(buffer);
                string s;

                vector<string> line;

                // ��������� ������ �� ������������, ����� �������� ����
                for (int i = 0; i < 3; i++)
                {
                    getline(ss, s, ' ');
                    if (i == 0)
                        line.push_back(s);
                }

                // ��������� ������ �� ���������
                line.push_back(to_string(idx * LENGTH));

                // ���������� ���������� ������ � ����
                pointer_table.push_back(line);

                idx++;
            }

            // ������� �������� � �����
            pointer_table.pop_back();

            // ��������� ���������� � ������� �������
            this->tableSize = pointer_table.size();

            pBinaryFile.close();
        }

        // ����� �� ����� �� ����� �� ������ � �������
        void print_table()
        {
            for (int i = 0; i < pointer_table.size() + 1; i++)
            {
                read_line(BINFILE, i);
            }
        }

        // ����� ������� � ������� � ��������
        void print_pointer_table()
        {

            for (int i = 0; i < pointer_table.size(); i++)
            {
                cout << setw(16) << pointer_table[i][0] << ' '
                     << setw(6) << pointer_table[i][1] << '\n';
            }
        }

        // �������� ������ �� ����� ����� �������
        void read_line(string fbname, int num)
        {
            // ��������� ������������ ���������� ������ ������
            if (num < 0 || num > pointer_table.size())
            {
                printf("Input error\n");
                return;
            }

            ifstream pBinaryFile(fbname, ios::in|ios::binary);

            // ���� ���� �� ������� �������
            if (!pBinaryFile.is_open())
            {
                printf("File '%s' doesn't exist\n", fbname.c_str());
                return;
            }

            char buffer[LENGTH] = "";

            // ���������� ���������� � ������ �����
            for (int i = 0; i < num; i++)
                pBinaryFile.read(buffer, LENGTH);

            // ���������� ����. ������
            pBinaryFile.read(buffer, LENGTH);
            cout << buffer << '\n';

            pBinaryFile.close();
        }

        // �������� �������
        vector<vector<string>> get_table()
        {
            return pointer_table;
        }

        // �������� �������� �����
        string get_key(int i)
        {
            return pointer_table[i][0];
        }
};

#endif // FILEMANANGER_H
