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
#include <vector>
using namespace std;

template <typename T, typename Comp = less<T>>
class BSTree : public Printer {
public:
    BSTree(Comp comp = Comp())
        : root_(nullptr)
        , comp_(comp) { }
    /// @brief 根据前序遍历和中序遍历构建二叉树
    BSTree(const vector<T>& preOrderVec, const vector<T>& inOrderVec) {
        root_ = build(preOrderVec, inOrderVec, 0, preOrderVec.size() - 1,
            0, inOrderVec.size() - 1);
    }
    ~BSTree() {
        // 层序遍历进行析构
        if (root_ != nullptr) {
            queue<Node*> qe;
            qe.push(root_);
            while (!qe.empty()) {
                Node* front = qe.front();
                qe.pop();

                if (front->left_ != nullptr) qe.push(front->left_);
                if (front->right_ != nullptr) qe.push(front->right_);
                delete front;
            }
            root_ = nullptr;
        }
    }

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

    /// @brief 搜索满足区间的元素值
    void findValues(vector<T>& vec, int i, int j) {
        findValues(root_, vec, i, j);
    }

    /// @brief 判断二叉树是否为BST树
    bool isBSTree() {
        Node* preNode = nullptr;
        return isBSTree(root_, preNode);
    }

    /// @brief 子树问题
    bool isChildTree(BSTree<T, Comp>& child) {
        // 在当前二叉树上找到子树的根节点
        if (child.root_ == nullptr) {
            return true;
        }

        Node* cur = root_;
        while (cur != nullptr) {
            if (cur->data_ == child.root_->data_) {
                break;
            } else if (comp_(cur->data_, child.root_->data_)) {
                cur = cur->right_;
            } else {
                cur = cur->left_;
            }
        }
        if (cur == nullptr) return false;
        return isChildTree(cur, child.root_);
    }

    /// @brief 最近的公共祖先
    T getLCA(T val1, T val2) {
        Node* node = getLCA(root_, val1, val2);
        if (node == nullptr) {
            throw "No LCA!";
        } else {
            return node->data_;
        }
    }

    /// @brief 镜像翻转
    void invertTree() {
        invertTree(root_);
    }

    /// @brief 镜像对称
    bool isSymmetricTree() {
        if (root_ == nullptr) return true;
        return isSymmetricTree(root_->left_, root_->right_);
    }

    /// @brief 判断是否为平衡树
    bool isBalanceTree() {
        bool res = true;
        isBalanceTree(root_, 0, res);
        return res;
    }

    /// @brief 求中序遍历倒数第k个节点
    int getVal(int k) {
        int   i    = 1;
        Node* node = getVal(root_, k);
        if (node == nullptr) {
            throw "Out of range!";
        } else {
            return node->data_;
        }
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

    /// @brief 递归搜索满足区间的元素值
    void findValues(Node* node, vector<T>& vec, int i, int j) {
        if (node != nullptr) {
            if (node->data_ > i) {
                // 如果当前节点的值小于等于左边界
                // 则当前节点的左子树没有必要去搜索
                findValues(node->left_, vec, i, j);
            }
            if (node->data_ >= i && node->data_ <= j) {
                vec.push_back(node->data_);
            }
            if (node->data_ < j) {
                // 如果当前结点的值大于等于右边界
                // 则当前节点的右子树没有必要去搜索
                findValues(node->right_, vec, i, j);
            }
        }
    }

    /// @brief 递归判断二叉树是否为BST树
    bool isBSTree(Node* node, Node*& preNode) {
        if (node == nullptr) return true;

        if (!isBSTree(node->left_, preNode)) {
            return false;
        }
        if (preNode != nullptr) {
            if (comp_(node->data_, preNode->data_)) {
                return false;
            }
        }
        preNode = node;
        return isBSTree(node->right_, preNode);
    }

    /// @brief 递归判断子树问题
    bool isChildTree(Node* father, Node* child) {
        if (father == nullptr && child == nullptr) return true;
        // 子树有 但是父树没有
        if (father == nullptr) return false;
        // 子树没有 但是父树有
        if (child == nullptr) return true;

        if (father->data_ != child->data_) {
            return false;
        }

        return isChildTree(father->left_, child->left_)
            && isChildTree(father->right_, child->right_);
    }

    /// @brief 递归搜索公共祖先
    Node* getLCA(Node* node, int val1, int val2) {
        if (node == nullptr) return nullptr;

        if (comp_(node->data_, val1) && comp_(node->data_, val2)) {
            return getLCA(node->right_, val1, val2);
        } else if (comp_(val1, node->data_) && comp_(val2, node->data_)) {
            return getLCA(node->left_, val1, val2);
        } else {
            return node;
        }
    }

    /// @brief 递归镜像翻转
    void invertTree(Node* node) {
        if (node == nullptr) return;

        Node* tmp    = node->left_;
        node->left_  = node->right_;
        node->right_ = tmp;

        invertTree(node->left_);
        invertTree(node->right_);
    }

    /// @brief 递归判断镜像对称
    bool isSymmetricTree(Node* node1, Node* node2) {
        if (node1 == nullptr && node2 == nullptr) return true;
        if (node1 == nullptr || node2 == nullptr) return false;

        if (node1->data_ != node2->data_)
            return false;
        return isSymmetricTree(node1->left_, node2->right_)
            && isSymmetricTree(node1->right_, node2->left_);
    }

    /**
     * @brief 根据前序遍历和中序遍历递归构建二叉树
     *
     * @param preOrderVec 前序序列
     * @param inOrderVec 中序序列
     * @param preStart 前序序列的起始索引
     * @param preEnd 前序序列的结束索引
     * @param inStart 中序序列的起始索引
     * @param inEnd 中序序列的结束索引
     */
    Node* build(const vector<T>& preOrderVec, const vector<T>& inOrderVec,
        int preStart, int preEnd, int inStart, int inEnd) {
        if (preStart > preEnd || inStart > inEnd) return nullptr;

        // 创建当前子树的根节点
        Node* node = new Node(preOrderVec[preStart]);
        for (int i = inStart; i <= inEnd; i++) {
            // 在中序序列中找寻目标元素 即为当前子树的根节点
            if (preOrderVec[preStart] == inOrderVec[i]) {
                node->left_  = build(preOrderVec, inOrderVec, preStart + 1,
                     preStart + (i - inStart), inStart, i - 1);
                node->right_ = build(preOrderVec, inOrderVec,
                    preStart + (i - inStart) + 1, preEnd, i + 1, inEnd);
                return node;
            }
        }
        return node;
    }

    /// @brief 递归判断是否为平衡树
    int isBalanceTree(Node* node, int l, bool& flag) {
        if (node == nullptr) return l;

        int left = isBalanceTree(node->left_, l + 1, flag);
        if (!flag) return left;
        int right = isBalanceTree(node->right_, l + 1, flag);
        if (!flag) return right;

        if (abs(left - right) > 1) {
            flag = false;
        }
        return max(left, right);
    }

    int i = 1;
    /// @brief 求中序遍历倒数第k个节点
    Node* getVal(Node* node, int k) {
        if (node == nullptr) return nullptr;

        int   tmp   = i + 1;
        Node* right = getVal(node->right_, k);
        if (right != nullptr) {
            return right;
        }
        if (i++ == k) {
            return node;
        }
        return getVal(node->left_, k);
    }
};

#endif // !_BINEARY_SEARCH_TREE_H