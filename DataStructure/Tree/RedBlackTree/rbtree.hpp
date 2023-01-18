/**
 * @file rbtree.hpp
 * @brief 红黑树的实现
 * @author Leaos
 * @date 2023-01-17
 */

#ifndef _RED_BLACK_TREE_H_
#define _RED_BLACK_TREE_H_

#include "printer.hpp"
#include <queue>
#include <iostream>
using namespace std;

template <typename T>
class RBTree : public Printer {
public:
    RBTree()
        : root_(nullptr) { }
    ~RBTree() {
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

    /// @brief 插入操作
    void insert(const T& val) {
        if (root_ == nullptr) {
            root_ = new Node(val);
            return;
        }

        Node* parent = nullptr;
        Node* cur    = root_;
        while (cur != nullptr) {
            if (cur->data_ > val) {
                parent = cur;
                cur    = cur->left_;
            } else if (cur->data_ < val) {
                parent = cur;
                cur    = cur->right_;
            } else {
                return;
            }
        }

        Node* node = new Node(val, parent, nullptr, nullptr, RED);
        if (parent->data_ > val) {
            parent->left_ = node;
        } else {
            parent->right_ = node;
        }

        // 如果新插入节点的父节点为红色 不满足红黑树性质 则调整红黑树
        if (RED == color(parent)) {
            fixAfterInsert(node);
        }
    }

    /// @brief 删除操作
    void remove(const T& val) {
        if (root_ == nullptr) return;

        Node* cur = root_;
        while (cur != nullptr) {
            if (cur->data_ > val) {
                cur = cur->left_;
            } else if (cur->data_ < val) {
                cur = cur->right_;
            } else {
                break;
            }
        }

        // 没有找到目标节点 返回
        if (cur == nullptr) return;

        // 删除cur节点
        if (cur->left_ != nullptr && cur->right_ != nullptr) {
            // 情况3，找寻前驱节点
            Node* pre = cur->left_;
            while (pre->right_ != nullptr) {
                pre = pre->right_;
            }
            cur->data_ = pre->data_;
            cur        = pre;
        }

        // 处理情况1和情况2
        Node* child = cur->left_;
        if (child != nullptr) {
            child = cur->right_;
        }

        if (child != nullptr) {
            child->parent_ = cur->parent_;
            if (cur->parent_ == nullptr) {
                // 删除的是根节点 更新根节点
                root_ = child;
            } else {
                if (cur->parent_->left_ == cur) {
                    cur->parent_->left_ = child;
                } else {
                    cur->parent_->right_ = child;
                }
            }

            Color c = color(cur);
            delete cur;

            if (c == BLACK) {
                // 如果删除的是黑色节点 需要进行节点调整
                fixAfterRemove(child);
            }
        } else {
            if (cur->parent_ == nullptr) {
                // 删除的cur为根节点
                delete cur;
                root_ = nullptr;
                return;
            } else {
                // 删除的cur为叶子节点
                if (color(cur) == BLACK) {
                    fixAfterRemove(cur);
                }

                if (cur->parent_->left_ == cur) {
                    cur->parent_->left_ = nullptr;
                } else {
                    cur->parent_->right_ = nullptr;
                }

                delete cur;
            }
        }
    }

protected:
    /// @brief 继承自Printer 实现如下函数以打印二叉树
    void*  getRoot() const { return (void*)root_; }
    void*  getLeft(void* node) const { return (Node*)(((Node*)node)->left_); }
    void*  getRight(void* node) const { return (Node*)(((Node*)node)->right_); }
    string getString(void* node) const { return to_string(((Node*)node)->data_); }
    bool   IsRed(void* node) const { return ((Node*)node)->color_ == RED; }

private:
    /// @brief 红黑树节点颜色
    enum Color {
        BLACK,
        RED
    };

    /// @brief 节点类型
    struct Node {
        Node(T data = T(), Node* parent = nullptr,
            Node* left = nullptr, Node* right = nullptr,
            Color color = Color::BLACK)
            : data_(data)
            , left_(left)
            , right_(right)
            , parent_(parent)
            , color_(color) { }

        T     data_;
        Node* left_;
        Node* right_;
        Node* parent_;
        Color color_;
    };

    Color color(Node* node) { return node == nullptr ? BLACK : node->color_; }
    void  setColor(Node* node, Color color) { node->color_ = color; }
    Node* left(Node* node) { return node->left_; }
    Node* right(Node* node) { return node->right_; }
    Node* parent(Node* node) { return node->parent_; }

    void leftRotate(Node* node) {
        Node* child    = node->right_;
        child->parent_ = node->parent_;
        if (node->parent_ == nullptr) {
            root_ = child; // 如果node本身是根节点
        } else {
            if (node->parent_->left_ == node) {
                // 如果node是父节点的左孩子
                node->parent_->left_ = child;
            } else {
                // 如果node是父节点的右孩子
                node->parent_->right_ = child;
            }
        }

        node->right_ = child->left_;
        if (child->left_ != nullptr) {
            child->left_->parent_ = node;
        }

        child->left_  = node;
        node->parent_ = child;
    }

    void rightRotate(Node* node) {
        Node* child    = node->left_;
        child->parent_ = node->parent_;
        if (node->parent_ == nullptr) {
            root_ = child; // 如果node原来就是root节点
        } else {
            if (node->parent_->left_ == node) {
                // node在父节点的左边
                node->parent_->left_ = child;
            } else {
                // node在父节点的右边
                node->parent_->right_ = child;
            }
        }

        node->left_ = child->right_;
        if (child->right_ != nullptr) {
            child->right_->parent_ = node;
        }

        child->right_ = node;
        node->parent_ = child;
    }

    /// @brief 红黑树的插入调整操作
    void fixAfterInsert(Node* node) {
        Node* father      = parent(node);
        Node* grandfather = parent(father);
        while (color(father) == RED) {
            if (left(grandfather) == father) {
                // 如果插入的节点在左子树中
                Node* uncle = right(grandfather);
                if (RED == color(uncle)) {
                    // 情况1：叔叔为红色
                    setColor(father, BLACK);
                    setColor(grandfather, RED);
                    setColor(uncle, BLACK);
                    // 继续向上调整
                    node = grandfather;
                } else {
                    // 先处理情况3：叔叔节点为黑色且新节点、父节点、祖父节点不在一侧
                    if (right(father) == node) {
                        leftRotate(father);
                        node        = father;
                        father      = parent(node);
                        grandfather = parent(father);
                    }

                    // 统一处理情况2：叔叔节点为黑色且新节点、父节点、祖父节点在一侧
                    setColor(father, BLACK);
                    setColor(grandfather, RED);
                    rightRotate(grandfather);
                    break; // 调整完成
                }
            } else {
                // 如果插入的节点在右子树中
                Node* uncle = left(grandfather);
                if (RED == color(uncle)) {
                    // 情况1：叔叔为红色
                    setColor(father, BLACK);
                    setColor(grandfather, RED);
                    setColor(uncle, BLACK);
                    // 继续向上调整
                    node = grandfather;
                } else {
                    // 先处理情况3：叔叔节点为黑色且新节点、父节点、祖父节点不在一侧
                    if (left(father) == node) {
                        rightRotate(father);
                        node        = father;
                        father      = parent(node);
                        grandfather = parent(father);
                    }

                    // 统一处理情况2：叔叔节点为黑色且新节点、父节点、祖父节点在一侧
                    setColor(father, BLACK);
                    setColor(grandfather, RED);
                    leftRotate(grandfather);
                    break; // 调整完成
                }
            }
        }

        // 将根节点强制为黑色 以满足红黑树的性质
        setColor(root_, BLACK);
    }

    /// @brief 红黑树的删除调整操作
    void fixAfterRemove(Node* node) {
        while (node != root_ && color(node) == BLACK) {
            if (left(parent(node)) == node) {
                // 如果删除的节点在左子树
                Node* brother = right(parent(node));
                if (color(brother) == RED) {
                    // 情况4：兄弟节点为红色
                    setColor(parent(node), RED);
                    setColor(brother, BLACK);
                    leftRotate(parent(node));
                    brother = right(parent(node));
                }

                if (color(left(brother)) == BLACK
                    && color(right(brother)) == BLACK) {
                    // 情况3：兄弟节点为黑色 且兄弟节点的左右孩子也为黑色
                    setColor(brother, RED);
                    node = parent(node);
                } else {
                    if (color(right(brother)) != RED) {
                        // 情况2：兄弟节点的左孩子为红色
                        setColor(brother, RED);
                        setColor(left(brother), BLACK);
                        rightRotate(brother);
                        brother = right(parent(node));
                    }

                    // 情况1：兄弟节点的右孩子为红色
                    setColor(brother, color(parent(node)));
                    setColor(parent(node), BLACK);
                    setColor(right(brother), BLACK);
                    leftRotate(parent(node));
                    break;
                }
            } else {
                // 如果删除的节点在右子树
                Node* brother = left(parent(node));
                if (color(brother) == RED) {
                    // 情况4：兄弟节点为红色
                    setColor(parent(node), RED);
                    setColor(brother, BLACK);
                    rightRotate(parent(node));
                    brother = left(parent(node));
                }

                if (color(left(brother)) == BLACK
                    && color(right(brother)) == BLACK) {
                    // 情况3：兄弟节点为黑色 且兄弟节点的左右孩子也为黑色
                    setColor(brother, RED);
                    node = parent(node);
                } else {
                    if (color(left(brother)) != RED) {
                        // 情况2：兄弟节点的左孩子为红色
                        setColor(brother, RED);
                        setColor(right(brother), BLACK);
                        leftRotate(brother);
                        brother = left(parent(node));
                    }

                    // 情况1：兄弟节点的右孩子为红色
                    setColor(brother, color(parent(node)));
                    setColor(parent(node), BLACK);
                    setColor(left(brother), BLACK);
                    rightRotate(parent(node));
                    break;
                }
            }
        }

        // 如果node指向的节点是红色 直接涂成黑色即可
        setColor(node, BLACK);
    }

    Node* root_;
};

#endif // !_RED_BLACK_TREE_H_