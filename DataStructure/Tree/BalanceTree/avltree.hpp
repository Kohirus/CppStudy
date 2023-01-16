/**
 * @file avltree.hpp
 * @brief AVL树(二叉平衡树)的实现
 * @author Leaos
 * @date 2023-01-16
 */

#ifndef _AVLTREE_H_
#define _AVLTREE_H_

#include "printer.hpp"
#include <string>
#include <queue>
using namespace std;

template <typename T>
class AVLTree : public Printer {
public:
    AVLTree()
        : root_(nullptr) { }
    ~AVLTree() {
        // 层序遍历清空资源
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
        }
    }

    /// @brief 插入
    void insert(const T& val) {
        root_ = insert(root_, val);
    }

    /// @brief 删除
    void remove(const T& val) {
        root_ = remove(root_, val);
    }

protected:
    /// @brief 继承自Printer 实现如下函数以打印二叉树
    void*  getRoot() const { return (void*)root_; }
    void*  getLeft(void* node) const { return (Node*)(((Node*)node)->left_); }
    void*  getRight(void* node) const { return (Node*)(((Node*)node)->right_); }
    string getString(void* node) const { return to_string(((Node*)node)->data_); }

private:
    /// @brief 节点定义
    struct Node {
        Node(T data = T())
            : data_(data)
            , left_(nullptr)
            , right_(nullptr)
            , height_(1) { }
        T     data_;
        Node* left_;
        Node* right_;
        int   height_;
    };

    /// @brief 返回节点的高度值
    int height(Node* node) {
        return node == nullptr ? 0 : node->height_;
    }

    /// @brief 对node做右旋转操作并将旋转后的根节点返回
    Node* rightRotate(Node* node) {
        // 节点旋转
        Node* child   = node->left_;
        node->left_   = child->right_;
        child->right_ = node;
        // 更新高度
        node->height_  = max(height(node->left_), height(node->right_)) + 1;
        child->height_ = max(height(child->left_), height(child->right_)) + 1;
        return child;
    }

    /// @brief 对node做左旋转操作并将旋转后的根节点返回
    Node* leftRotate(Node* node) {
        // 节点旋转
        Node* child  = node->right_;
        node->right_ = child->left_;
        child->left_ = node;
        // 更新高度
        node->height_  = max(height(node->left_), height(node->right_)) + 1;
        child->height_ = max(height(child->left_), height(child->right_)) + 1;
        return child;
    }

    /// @brief 左平衡操作
    Node* leftBalance(Node* node) {
        node->left_ = leftRotate(node->left_);
        return rightRotate(node);
    }

    /// @brief 右平衡操作
    Node* rightBalance(Node* node) {
        node->right_ = rightRotate(node->right_);
        return leftRotate(node);
    }

    /// @brief 通过递归进行插入
    Node* insert(Node* node, const T& val) {
        if (node == nullptr) return new Node(val);

        if (node->data_ > val) {
            node->left_ = insert(node->left_, val);
            // 如果当前节点的左子树太高
            if (height(node->left_) - height(node->right_) > 1) {
                if (height(node->left_->left_) >= height(node->left_->right_)) {
                    // 如果左孩子的左子树太高
                    node = rightRotate(node);
                } else {
                    // 如果左孩子的右子树太高
                    node = leftBalance(node);
                }
            }
        } else if (node->data_ < val) {
            node->right_ = insert(node->right_, val);
            // 如果当前节点的右子树太高
            if (height(node->right_) - height(node->left_) > 1) {
                if (height(node->right_->right_) >= height(node->right_->left_)) {
                    // 如果右孩子的右子树太高
                    node = leftRotate(node);
                } else {
                    // 如果右孩子的左子树太高
                    node = rightBalance(node);
                }
            }
        }

        // 递归回溯时 更新节点高度
        node->height_ = max(height(node->left_), height(node->right_)) + 1;

        return node;
    }

    /// @brief 递归删除
    Node* remove(Node* node, const T& val) {
        if (node == nullptr) return nullptr;

        if (node->data_ > val) {
            node->left_ = remove(node->left_, val);
            // 左子树删除节点 可能造成右子树太高
            if (height(node->right_) - height(node->left_) > 1) {
                if (height(node->right_->right_) >= height(node->right_->left_)) {
                    // 右孩子的右子树太高
                    node = leftRotate(node);
                } else {
                    // 右孩子的左子树太高
                    node = rightBalance(node);
                }
            }
        } else if (node->data_ < val) {
            node->right_ = remove(node->right_, val);
            // 右子树删除节点 可能造成左子树太高
            if (height(node->left_) - height(node->right_) > 1) {
                if (height(node->left_->left_) >= height(node->left_->right_)) {
                    // 左孩子的左子树太高
                    node = rightRotate(node);
                } else {
                    // 左孩子的右子树太高
                    node = leftBalance(node);
                }
            }
        } else {
            // 找到待删除节点

            // 情况3: 左子节点和右子节点均不为空
            if (node->left_ != nullptr && node->right_ != nullptr) {
                // 避免删除前驱或者后继节点造成节点失衡 谁高删谁
                if (height(node->left_) >= height(node->right_)) {
                    // 删除前驱节点
                    Node* pre = node->left_;
                    while (pre->right_ != nullptr) {
                        pre = pre->right_;
                    }
                    node->data_ = pre->data_;
                    node->left_ = remove(node->left_, pre->data_);
                } else {
                    // 删除后继节点
                    Node* nxt = node->right_;
                    while (nxt->left_ != nullptr) {
                        nxt = nxt->left_;
                    }
                    node->data_  = nxt->data_;
                    node->right_ = remove(node->right_, nxt->data_);
                }
            } else {
                // 情况1或情况2: 最多只有一个节点不为空
                if (node->left_ != nullptr) {
                    Node* left = node->left_;
                    delete node;
                    return left;
                } else if (node->right_ != nullptr) {
                    Node* right = node->right_;
                    delete node;
                    return right;
                } else {
                    return nullptr;
                }
            }
        }

        // 在回溯的过程中更新节点高度
        node->height_ = max(height(node->left_), height(node->right_)) + 1;

        return node;
    }

private:
    Node* root_;
};

#endif // !_AVLTREE_H_