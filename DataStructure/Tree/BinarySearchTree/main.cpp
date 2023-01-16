#include <iostream>
#include <vector>
#include "bstree.hpp"
using namespace std;

int main() {
    // 通过Lambda表达式构建自定义类型的二叉树
    /*
    using Elem    = pair<int, string>;
    using Functor = function<bool(Elem, Elem)>;
    BSTree<Elem, Functor> bst([](Elem p1, Elem p2) -> bool {
        return p1.first == p2.first;
    });
    */

    BSTree<int>
        tree;
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

    // 中序遍历倒数第k个节点
    int k = 3;
    cout << "Reciprocal " << k << " : " << tree.getVal(k) << endl;

    // 子树问题
    cout << endl;
    BSTree<int> child;
    child.insert(67);
    child.insert(62);
    child.insert(60);
    child.insert(64);
    child.insert(69);
    child.insert(78);
    cout << "Child Tree:" << endl;
    cout << child << endl;
    if (tree.isChildTree(child)) {
        cout << "Is child tree!" << endl;
    } else {
        cout << "Is not child tree!" << endl;
    }
    cout << endl;
    child.insert(68);
    cout << "Child Tree:" << endl;
    cout << child << endl;
    if (tree.isChildTree(child)) {
        cout << "Is child tree!" << endl;
    } else {
        cout << "Is not child tree!" << endl;
    }
    cout << endl;

    // 最近的公共祖先
    cout << "LCA:" << endl;
    cout << "41 and 60: " << tree.getLCA(41, 60) << endl;
    cout << "64 and 78: " << tree.getLCA(64, 78) << endl;
    cout << "62 and 69: " << tree.getLCA(62, 69) << endl;
    cout << endl;

    // 镜像翻转
    cout << "Invert:" << endl;
    tree.invertTree();
    cout << tree << endl;
    tree.invertTree();
    cout << endl;

    // 镜像对称
    cout << "Symmetric:" << endl;
    if (tree.isSymmetricTree()) {
        cout << "Is symmetric tree!" << endl;
    } else {
        cout << "Is not symmetric tree!" << endl;
    }
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

    // 是否为平衡树
    if (tree.isBalanceTree())
        cout << "Is balance tree!" << endl;
    else
        cout << "Is not balance tree!" << endl;
    cout << endl;
    tree.remove(5);
    tree.remove(34);
    cout << tree << endl;
    if (tree.isBalanceTree())
        cout << "Is balance tree!" << endl;
    else
        cout << "Is not balance tree!" << endl;
    cout << endl;
    tree.insert(5);
    tree.insert(34);

    // 非递归查询
    if (tree.search(5))
        cout << "Exist 5!" << endl;
    else
        cout << "Not Exist 5!" << endl;
    if (tree.r_search(78))
        cout << "Exist 78!" << endl;
    else
        cout << "Not Exist 78!" << endl;

    // 查找区间元素
    cout << endl;
    cout << "Search interval element: ";
    vector<int> vec;
    tree.findValues(vec, 10, 60);
    for (int val : vec) cout << val << " ";
    cout << endl;

    // 是否为BST树
    cout << endl;
    if (tree.isBSTree())
        cout << "Is BSTree!" << endl;
    else
        cout << "Is not BSTree!" << endl;

    // 根据前序遍历和后序遍历重建二叉树
    cout << endl;
    cout << "Rebuild tree: " << endl;
    vector<int> perOrderVec = { 58, 24, 0, 50, 34, 41, 67, 62, 60, 64, 69, 78 };
    vector<int> inOrderVec  = { 0, 5, 24, 34, 41, 58, 60, 62, 64, 67, 69, 78 };
    BSTree<int> newTree(perOrderVec, inOrderVec);
    cout << newTree << endl;

    return 0;
}