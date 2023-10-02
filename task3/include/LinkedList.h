#ifndef LINKEDLIST_H
#define LINKEDLIST_H

// Связный список
struct LinkedList {
    int id;             // Ключ
    string fullName;
    string adress;
    LinkedList* next;   // Указатель на следующий элемент списка
    LinkedList(int id_ = 0, string fn = "none", string a = "") : id(id_), fullName(fn), adress(a), next(nullptr) {}

    // Проверка на наличие 'пустой' ячейки в хеш-таблице
    bool is_empty()
    {
        return fullName == "none"; // Пустота здесь - запись в поле имени по умолчанию
    }

    // Добавляет элемент в таблицу
    void set(int id, string fullName, string adress)
    {
        if (!is_empty()) // Если ячейка заполнена
        {
            // Всатвляем элемент в конец списка
            if (this->next == nullptr)
                this->next = new LinkedList(id, fullName, adress);
            else
                this->next->set(id, fullName, adress);
        }
        else // Если ячейка пуста
        {
            this->id = id;
            this->fullName = fullName;
            this->adress = adress;
        }
    }

    // Возвращает элемент из ячейки таблицы в виде строки
    string get()
    {
        if (is_empty())
            return fullName;
        return "{" + to_string(id) + ", '" + fullName + "', '" + adress + "'}";
    }

    // Возвращает список элемент из ячейки таблицы в виде строки
    string get_list()
    {
        if (is_empty())
            return fullName;

        if (this->next == nullptr)
            return "{" + to_string(id) + ", '" + fullName + "', '" + adress + "'}";

        // Рекурентный вывод полей из каждого элемента списка
        return "{" + to_string(id) + ", '" + fullName + "', '" + adress + "'} - " + next->get_list();
    }
};

#endif // LINKEDLIST_H
