#include <iostream>
#include "TreeAVL.h" // Импорт данных для АВЛ дерева

using namespace std;

int main() {
    // Вставка в АВЛ дерево узлов с ключами от 0 до 9
    Node* root = new Node(0);
    for (int i = 1; i <= 9; i++)
        insert(root, i);

    // Симмеричный и обратный обходы
    cout << "Symmetric traversal:\n";
    symmetric_traversal(root);
    cout << '\n';
    cout << "Reverse traversal:\n";
    reverse_traversal(root);
    cout << '\n';

    // Поиск высоты дерева
    cout << "Height: " << get_height(root) << endl;
    // Поиск расстояния между узлами с ключами 0 и 9
    cout << "Distance (between 0 and 9): " << get_distance(root, root->right->right->right) << endl;
    // Поиск среднего арифметического (сумма ключей дерева делить на их кол-во)
    cout << "Sum: " << get_sum(root) << endl;
    cout << "Count: " << get_count(root) << endl;
    cout << "Mean: " << get_mean(root) << endl;

    return 0;
}
