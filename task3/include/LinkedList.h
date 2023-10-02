#ifndef LINKEDLIST_H
#define LINKEDLIST_H

// ������� ������
struct LinkedList {
    int id;             // ����
    string fullName;
    string adress;
    LinkedList* next;   // ��������� �� ��������� ������� ������
    LinkedList(int id_ = 0, string fn = "none", string a = "") : id(id_), fullName(fn), adress(a), next(nullptr) {}

    // �������� �� ������� '������' ������ � ���-�������
    bool is_empty()
    {
        return fullName == "none"; // ������� ����� - ������ � ���� ����� �� ���������
    }

    // ��������� ������� � �������
    void set(int id, string fullName, string adress)
    {
        if (!is_empty()) // ���� ������ ���������
        {
            // ��������� ������� � ����� ������
            if (this->next == nullptr)
                this->next = new LinkedList(id, fullName, adress);
            else
                this->next->set(id, fullName, adress);
        }
        else // ���� ������ �����
        {
            this->id = id;
            this->fullName = fullName;
            this->adress = adress;
        }
    }

    // ���������� ������� �� ������ ������� � ���� ������
    string get()
    {
        if (is_empty())
            return fullName;
        return "{" + to_string(id) + ", '" + fullName + "', '" + adress + "'}";
    }

    // ���������� ������ ������� �� ������ ������� � ���� ������
    string get_list()
    {
        if (is_empty())
            return fullName;

        if (this->next == nullptr)
            return "{" + to_string(id) + ", '" + fullName + "', '" + adress + "'}";

        // ����������� ����� ����� �� ������� �������� ������
        return "{" + to_string(id) + ", '" + fullName + "', '" + adress + "'} - " + next->get_list();
    }
};

#endif // LINKEDLIST_H
