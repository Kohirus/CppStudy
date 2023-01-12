#include <iostream>
#include "bstree.hpp"
using namespace std;

int main() {
    BSTree<int> tree;
    tree.insert(58);
    tree.r_insert(24);
    tree.insert(0);
    tree.r_insert(5);
    tree.insert(34);
    tree.r_insert(41);
    tree.insert(67);
    tree.r_insert(62);
    tree.insert(60);
    tree.r_insert(64);
    tree.insert(69);
    tree.r_insert(78);
    cout << tree << endl;

    cout << "BST Tree High: " << tree.level() << endl;
    cout << "BST Tree Size: " << tree.size() << endl;
    cout << endl;

    // 递归前序遍历 中序遍历 后序遍历 层序遍历
    tree.r_preOrder();
    tree.r_inOrder();
    tree.r_postOrder();
    tree.r_levelOrder();
    cout << endl;

    // 非递归前序遍历 中序遍历 后序遍历 层序遍历
    tree.preOrder();
    tree.inOrder();
    tree.postOrder();
    tree.levelOrder();
    cout << endl;

    // 删除没有孩子的节点
    tree.remove(78);
    cout << tree << endl;

    // 删除只有一个孩子的节点
    tree.r_remove(0);
    cout << tree << endl;

    // 删除有两个孩子的节点
    tree.remove(62);
    cout << tree << endl;

    // 删除根节点
    tree.r_remove(58);
    cout << tree << endl;

    // 非递归查询
    if (tree.search(5))
        cout << "Exist 5!" << endl;
    else
        cout << "Not Exist 5!" << endl;
    if (tree.r_search(78))
        cout << "Exist 78!" << endl;
    else
        cout << "Not Exist 78!" << endl;

    return 0;
}