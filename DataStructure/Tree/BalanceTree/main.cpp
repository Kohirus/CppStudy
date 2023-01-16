#include <iostream>
#include "avltree.hpp"
using namespace std;

int main() {
    AVLTree<int> tree;

    // 插入节点
    for (int i = 1; i <= 10; i++) {
        cout << "Insert number: " << i << endl;
        tree.insert(i);
        cout << tree << endl;
        cout << "=====================================" << endl;
    }

    // 删除节点
    for (int i = 10; i > 0; i--) {
        cout << "Remove number: " << i << endl;
        tree.remove(i);
        cout << tree << endl;
        cout << "=====================================" << endl;
    }

    return 0;
}