/**
 * @file bstree.hpp
 * @brief BST树(二叉搜索树)的实现
 * @author Leaos
 * @date 2023-01-09
 */

#ifndef _BINEARY_SEARCH_TREE_H_
#define _BINEARY_SEARCH_TREE_H

#include <functional>
#include "printer.hpp"
#include <string>
#include <stack>
#include <queue>
using namespace std;

template <typename T, typename Comp = less<T>>
class BSTree : public Printer {
public:
    BSTree()
        : root_(nullptr) { }
    ~BSTree() { }

    /// @brief 非递归插入
    void insert(const T& val) {
        if (root_ == nullptr) {
            root_ = new Node(val);
            return;
        }

        Node *cur = root_, *parent = nullptr;
        while (cur != nullptr) {
            if (cur->data_ == val) {
                break;
            } else if (comp_(cur->data_, val)) {
                parent = cur;
                cur    = cur->right_;
            } else {
                parent = cur;
                cur    = cur->left_;
            }
        }

        if (comp_(val, parent->data_)) {
            parent->left_ = new Node(val);
        } else {
            parent->right_ = new Node(val);
        }
    }

    /// @brief 递归插入
    void r_insert(const T& val) {
        root_ = r_insert(root_, val);
    }

    /// @brief 非递归删除
    void remove(const T& val) {
        if (root_ == nullptr) return;

        Node *parent = nullptr, *cur = root_;
        while (cur != nullptr) {
            if (cur->data_ == val) {
                break;
            } else if (comp_(cur->data_, val)) {
                parent = cur;
                cur    = cur->right_;
            } else {
                parent = cur;
                cur    = cur->left_;
            }
        }

        // 未找到待删除节点
        if (cur == nullptr) return;

        // 处理情况3
        if (cur->left_ != nullptr && cur->right_ != nullptr) {
            parent    = cur;
            Node* pre = cur->left_;
            while (pre->right_ != nullptr) {
                parent = pre;
                pre    = pre->right_;
            }
            cur->data_ = pre->data_;
            cur        = pre; // 让cur指向前驱节点 转化为情况1或情况2
        }

        // 处理情况1或情况2
        // cur指向待删除节点 parent指向其父节点
        Node* child = cur->left_;
        if (child == nullptr) {
            child = cur->right_;
        }

        if (parent == nullptr) {
            // 表示删除的是根节点
            root_ = child;
        } else {
            // 将待删除节点写入其父节点的相应地址域
            if (parent->left_ == cur) {
                parent->left_ = child;
            } else {
                parent->right_ = child;
            }
        }

        delete cur;
    }

    /// @brief 递归删除
    void r_remove(const T& val) {
        root_ = r_remove(root_, val);
    }

    /// @brief 非递归查询
    bool search(const T& val) {
        Node* cur = root_;
        while (cur != nullptr) {
            if (cur->data_ == val) {
                return true;
            } else if (comp_(cur->data_, val)) {
                cur = cur->right_;
            } else {
                cur = cur->left_;
            }
        }
        return false;
    }

    /// @brief 递归查询
    bool r_search(const T& val) {
        return r_search(root_, val) != nullptr;
    }

    /// @brief 递归前序遍历
    void r_preOrder() {
        cout << "[Recursion]Preorder Traversal: ";
        r_preOrder(root_);
        cout << endl;
    }

    /// @brief 非递归前序遍历
    void preOrder() {
        cout << "[Not Recursion]Preorder Traversal: ";
        if (root_ == nullptr) return;
        stack<Node*> st;
        st.push(root_);
        while (!st.empty()) {
            Node* top = st.top();
            st.pop();

            cout << top->data_ << " ";

            if (top->right_ != nullptr) st.push(top->right_);
            if (top->left_ != nullptr) st.push(top->left_);
        }
        cout << endl;
    }

    /// @brief 递归中序遍历
    void r_inOrder() {
        cout << "[Recursion]Inorder Traversal: ";
        r_inOrder(root_);
        cout << endl;
    }

    /// @brief 非递归中序遍历
    void inOrder() {
        cout << "[Not Recursion]Inorder Traversal: ";
        if (root_ == nullptr) return;
        stack<Node*> st;
        Node*        cur = root_;
        while (cur != nullptr) {
            st.push(cur);
            cur = cur->left_;
        }

        while (!st.empty() || cur != nullptr) {
            if (cur != nullptr) {
                st.push(cur);
                cur = cur->left_;
            } else {
                Node* top = st.top();
                st.pop();
                cout << top->data_ << " ";
                cur = top->right_;
            }
        }
        cout << endl;
    }

    /// @brief 递归后序遍历
    void r_postOrder() {
        cout << "[Recursion]Postorder Traversal: ";
        r_postOrder(root_);
        cout << endl;
    }

    /// @brief 非递归后序遍历
    void postOrder() {
        cout << "[Not Recursion]Postorder Traversal: ";
        if (root_ == nullptr) return;
        stack<Node*> st, tmp;
        st.push(root_);
        while (!st.empty()) {
            Node* top = st.top();
            st.pop();
            tmp.push(top);
            if (top->left_ != nullptr) st.push(top->left_);
            if (top->right_ != nullptr) st.push(top->right_);
        }
        while (!tmp.empty()) {
            Node* top = tmp.top();
            cout << top->data_ << " ";
            tmp.pop();
        }
        cout << endl;
    }

    /// @brief 递归层序遍历
    void r_levelOrder() {
        cout << "[Recursion]Levelorder Traversal: ";
        int l = level();
        for (int i = 0; i < l; i++) {
            r_levelOrder(root_, i);
        }
        cout << endl;
    }

    /// @brief 非递归层序遍历
    void levelOrder() {
        cout << "[Not Recursion]Levelorder Traversal: ";
        if (root_ == nullptr) return;
        queue<Node*> qe;
        qe.push(root_);
        while (!qe.empty()) {
            Node* front = qe.front();
            if (front->left_ != nullptr) qe.push(front->left_);
            if (front->right_ != nullptr) qe.push(front->right_);
            qe.pop();
            cout << front->data_ << " ";
        }
        cout << endl;
    }

    /// @brief 返回二叉树的层数
    int level() const {
        return level(root_);
    }

    /// @brief 返回二叉树的节点个数
    int size() const {
        return size(root_);
    }

protected:
    /// @brief 继承自Printer 实现如下函数以打印二叉树
    void*  getRoot() const { return (void*)root_; }
    void*  getLeft(void* node) const { return (Node*)(((Node*)node)->left_); }
    void*  getRight(void* node) const { return (Node*)(((Node*)node)->right_); }
    string getString(void* node) const { return to_string(((Node*)node)->data_); }

private:
    /// @brief 树节点的定义
    struct Node {
        Node(T data = T())
            : data_(data)
            , left_(nullptr)
            , right_(nullptr) { }
        T     data_;
        Node* left_;
        Node* right_;
    };

    Node* root_;
    Comp  comp_;

private:
    /// @brief 递归插入
    Node* r_insert(Node* node, const T& val) {
        if (node == nullptr) return new Node(val);

        if (node->data_ == val) {
            return node;
        } else if (comp_(node->data_, val)) {
            node->right_ = r_insert(node->right_, val);
        } else {
            node->left_ = r_insert(node->left_, val);
        }
        return node;
    }

    /// @brief 递归删除
    Node* r_remove(Node* node, const T& val) {
        if (node == nullptr) return nullptr;

        if (node->data_ == val) {
            if (node->left_ != nullptr && node->right_ != nullptr) {
                // 情况3
                // 找前驱节点
                Node* pre = node->left_;
                while (pre->right_ != nullptr) {
                    pre = pre->right_;
                }
                node->data_ = pre->data_;
                // 通过递归删除前驱节点
                node->left_ = r_remove(node->left_, pre->data_);
            } else {
                // 情况1或情况2
                if (node->left_ != nullptr) {
                    Node* left = node->left_;
                    delete node;
                    return left;
                } else if (node->right_ != nullptr) {
                    Node* right = node->right_;
                    delete node;
                    return right;
                } else {
                    // 删除的是叶子节点
                    delete node;
                    return nullptr;
                }
            }
        } else if (comp_(node->data_, val)) {
            node->right_ = r_remove(node->right_, val);
        } else {
            node->left_ = r_remove(node->left_, val);
        }
        return node;
    }

    /// @brief 递归查询
    Node* r_search(Node* node, const T& val) {
        if (node == nullptr) return nullptr;

        if (node->data_ == val) {
            return node;
        } else if (comp_(node->data_, val)) {
            return r_search(node->right_, val);
        } else {
            return r_search(node->left_, val);
        }
    }

    /// @brief 递归前序遍历
    void r_preOrder(Node* node) {
        if (node == nullptr) return;

        cout << node->data_ << " ";
        r_preOrder(node->left_);
        r_preOrder(node->right_);
    }

    /// @brief 递归中序遍历
    void r_inOrder(Node* node) {
        if (node == nullptr) return;

        r_inOrder(node->left_);
        cout << node->data_ << " ";
        r_inOrder(node->right_);
    }

    /// @brief 递归后序遍历
    void r_postOrder(Node* node) {
        if (node == nullptr) return;

        r_postOrder(node->left_);
        r_postOrder(node->right_);
        cout << node->data_ << " ";
    }

    /// @brief 递归层序遍历
    void r_levelOrder(Node* node, int l) {
        if (node == nullptr) return;

        if (l == 0) {
            cout << node->data_ << " ";
            return;
        }
        r_levelOrder(node->left_, l - 1);
        r_levelOrder(node->right_, l - 1);
    }

    /// @brief 递归求二叉树的层数
    int level(Node* node) const {
        if (node == nullptr)
            return 0;
        int lcnt = level(node->left_);
        int rcnt = level(node->right_);
        return max(rcnt, lcnt) + 1;
    }

    /// @brief 递归求二叉树的节点个数
    int size(Node* node) const {
        if (node == nullptr) return 0;
        int lcnt = size(node->left_);
        int rcnt = size(node->right_);
        return rcnt + lcnt + 1;
    }
};

#endif // !_BINEARY_SEARCH_TREE_H