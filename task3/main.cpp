#include <iostream>

using namespace std;

#include "Hash.h"

#include <vector>

int main()
{
    Hash hash;

    int cmd;
    string fn, ad;

    while(cmd != -1)
    {
        cout << "Enter the number of command:\n"
             << "0) Print the hash-table\n"
             << "1) Insert data in the hash-table\n"
             << "2) Remove data from the hash-table\n"
             << "3) Get data from the hash-table by key\n"
             << "-1) Quit the program\n"
             << "Command: ";
        cin >> cmd;

        switch(cmd)
        {
        case -1:
            break;
        case 0:
            cout << "Print empty elements(1) or don't (0)? ";
            cin >> cmd;
            hash.print_table(cmd);
            break;
        case 1:
            cout << "Enter ID by format XXXXX: ";
            cin >> cmd;
            getline(cin, fn);
            cout << "Enter full name of owner: ";
            getline(cin, fn);
            cout << "Enter address of owner: ";
            getline(cin, ad);

            hash.to_hash(cmd, fn, ad);
            break;
        case 2:
            cout << "Enter ID by format XXXXX: ";
            cin >> cmd;
            hash.remove(cmd);
            break;
        case 3:
            cout << "Enter ID by format XXXXX: ";
            cin >> cmd;
            cout << hash.get_val(cmd) << '\n';
            break;
        default:
            cout << "Incorrect input data\n";
        }
        cout << "==========================================\n";
    }

    return 0;
}
