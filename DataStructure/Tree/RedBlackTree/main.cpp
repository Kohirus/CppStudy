#include <iostream>
#include "rbtree.hpp"
using namespace std;

int main() {
    RBTree<int> tree;

    tree.insert(80);
    tree.insert(40);
    tree.insert(120);
    tree.insert(20);
    tree.insert(60);
    tree.insert(100);
    tree.insert(140);
    tree.insert(10);
    tree.insert(50);
    tree.insert(90);
    tree.insert(130);
    tree.insert(150);
    cout << tree << endl;

    cout << "删除红色节点(40):" << endl;
    tree.remove(40);
    cout << tree << endl;

    cout << "删除黑色节点(100):" << endl;
    tree.remove(100);
    cout << tree << endl;

    cout << "删除黑色节点(60):" << endl;
    tree.remove(60);
    cout << tree << endl;

    cout << "删除黑色节点(120):" << endl;
    tree.remove(120);
    cout << tree << endl;
    return 0;
}