#ifndef TASK5_TREEAVL_H
#define TASK5_TREEAVL_H

#include <iostream>
using namespace std;

// Узел АВЛ дерева
struct Node {
    int key;                // Ключ
    unsigned char height;   // Высота
    Node* left;             // Левый ребенок
    Node* right;            // Правый ребенок

    // Конструктор, создающий узел
    Node(int k) {key = k; left = right = nullptr; height = 0; }
};

int get_height(Node* p) // Высота поддерева с корнем в данном узле
{
    return p ? p->height : -1;
}

int bfactor(Node* p)    // Разность между высотами левого и правого поддерева
{
    return p ? get_height(p->right) - get_height(p->left) : 0;
}

void fix_height(Node* p)    // Исправление высоты после вставки/балансировки дерева
{
    int hl = get_height(p->left);
    int hr = get_height(p->right);
    p->height = max(hl, hr) + 1;
}

void right_rotate(Node* p) {    // Правый поворот вокруг p
    swap(p->key, p->left->key);
    Node* buffer = p->right;
    p->right = p->left;
    p->left = p->right->left;
    p->right->left = p->right->right;
    p->right->right = buffer;

    fix_height(p->right);
    fix_height(p);
}

void left_rotate(Node* p) {     // Левый поворот вокруг p
    swap(p->key, p->right->key);
    Node* buffer = p->left;
    p->left = p->right;
    p->right = p->left->right;
    p->left->right = p->left->left;
    p->left->left = buffer;

    fix_height(p->left);
    fix_height(p);
}

void balance(Node* p) {     // Балансировка дерева
    if (bfactor(p) == -2) {
        if (bfactor(p->left) == 1) left_rotate(p->left);
        right_rotate(p);
    }
    else if (bfactor(p) == 2) {
        if (bfactor(p->right) == -1)right_rotate(p->right);
        left_rotate(p);
    }
}

void insert(Node* p, int k) {   // Вставка узла в дерево
    if (k < p->key) {
        if (p->left == nullptr)
            p->left = new Node(k);
        else
            insert(p->left, k);
    }
    else if (k > p->key) {
        if (p->right == nullptr)
            p->right = new Node(k);
        else
            insert(p->right, k);
    }
    else {
        printf("The key %d exists in the tree\n", k);
    }

    fix_height(p);
    balance(p);
}

void reverse_traversal(Node* p) {   // Обратный обход дерева
    if (!p) return;

    reverse_traversal(p->left);
    reverse_traversal(p->right);
    cout << p->key << ' ';
}

void symmetric_traversal(Node* p) { // Симмертричный обход дерева
    if (!p) return;

    symmetric_traversal(p->left);
    cout << p->key << ' ';
    symmetric_traversal(p->right);
}

int get_distance(Node* root, Node* p) {     // Поиск расстояние между корневым узлом и заданным
    return (root && p) ? get_height(root) - get_height(p): -1;
}

int get_sum(Node* p) {  // Вычисление суммы ключей узлов дерева
    if (!p) return 0;
    return p->key + get_sum(p->left) + get_sum(p->right);
}

int get_count(Node* p) {    // Вычисление количества узлов дерева
    if (!p) return 0;
    return 1 + get_count(p->left) + get_count(p->right);
}

double get_mean(Node* p) {  // Вычисление среднего арифметического дерева
    return static_cast<double>(get_sum(p)) / get_count(p);
}

#endif //TASK5_TREEAVL_H
