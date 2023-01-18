#include "printer.hpp"
#include <windows.h>
#include <queue>
#include <sstream>
#include <ostream>

class Printer::InfoNode {
public:
    std::string content;
    InfoNode*   parent;
    InfoNode*   left   = nullptr;
    InfoNode*   right  = nullptr;
    InfoNode*   next   = nullptr; // 同一层的下一个节点
    int         pos    = 0;       // 结点起始位置
    int         middle = 0;       // 结点中心距起始位置的距离
    int         last   = 0;       // 结点末尾距起始位置的距离
    bool        isred  = false;

public:
    InfoNode(const std::string& str, InfoNode* parent, bool isRed)
        : content(str)
        , parent(parent)
        , isred(isRed) { }
    ~InfoNode() {
        if (this->left)
            delete this->left;
        if (this->right)
            delete this->right;
        this->left  = nullptr;
        this->right = nullptr;
    }
};

Printer::~Printer() {
    if (this->root) {
        delete this->root;
        this->root = nullptr;
    }
}

void Printer::initTreeStructure() {
    if (this->root) {
        delete this->root;
        this->root = nullptr;
    }
    this->layerHead.clear();
    void* rootNode = this->getRoot();
    if (rootNode == nullptr)
        return;
    this->root         = this->initTreeStructure(rootNode, nullptr);
    this->root->middle = this->root->content.size() / 2;
    this->root->last   = this->root->content.size() - 1;
}

typename Printer::InfoNode* Printer::initTreeStructure(void* node, InfoNode* parent) {
    InfoNode* newNode = new InfoNode(this->getString(node), parent, this->IsRed(node));
    void*     left    = this->getLeft(node);
    void*     right   = this->getRight(node);
    if (left) {
        InfoNode* leftNode = this->initTreeStructure(left, newNode);
        leftNode->middle   = leftNode->content.size() / 2;
        leftNode->last     = leftNode->content.size() - 1;
        newNode->left      = leftNode;
    }
    if (right) {
        InfoNode* rightNode = this->initTreeStructure(right, newNode);
        rightNode->middle   = (rightNode->content.size() - 1) / 2;
        rightNode->last     = rightNode->content.size() - 1;
        newNode->right      = rightNode;
    }
    return newNode;
}

void Printer::setLayerLink() {
    if (this->root == nullptr)
        return;
    this->layerHead.clear();
    std::queue<InfoNode*> Q;
    Q.push(this->root);
    while (!Q.empty()) {
        this->layerHead.push_back(Q.front());
        int size = Q.size();
        while (size--) {
            InfoNode* cur = Q.front();
            Q.pop();
            if (size > 0)
                cur->next = Q.front();
            if (cur->left)
                Q.push(cur->left);
            if (cur->right)
                Q.push(cur->right);
        }
    }
}

void Printer::initPosInfo() {
    if (this->root == nullptr || this->layerHead.empty())
        return;
    this->root->pos = 0;
    for (size_t i = 1; i < this->layerHead.size(); i++) {
        InfoNode* cur = this->layerHead[i];
        while (cur) {
            if (cur == cur->parent->left) {
                cur->pos = cur->parent->pos - 2 - cur->middle;
            } else {
                cur->pos = cur->parent->pos + cur->parent->last + 2 - cur->middle;
            }
            cur = cur->next;
        }
    }
}

void Printer::agjustPosInfo() {
    if (this->root == nullptr)
        return;
    for (int i = this->layerHead.size() - 2; i >= 0; i--) {
        InfoNode* cur = this->layerHead[i];
        while (cur) {
            int cross = this->calcCrossLen(cur);
            if (cross > 0) {
                int left = cross / 2;
                this->movePos(cur->left, -left);
                this->movePos(cur->right, cross - left);
            }
            cur = cur->next;
        }
    }
    int minPos = 0;
    for (auto node : this->layerHead) {
        minPos = node->pos < minPos ? node->pos : minPos;
    }
    if (minPos < 0) {
        this->movePos(this->root, -minPos);
    }
}

int Printer::calcCrossLen(InfoNode* node) {
    if (node == nullptr || node->left == nullptr || node->right == nullptr)
        return 0;
    std::vector<int>      leftRight;
    std::vector<int>      rightLeft;
    std::queue<InfoNode*> Q;
    Q.push(node->left);
    while (!Q.empty()) {
        int size = Q.size();
        while (size > 1) {
            InfoNode* cur = Q.front();
            Q.pop();
            if (cur->left)
                Q.push(cur->left);
            if (cur->right)
                Q.push(cur->right);
            size--;
        }
        InfoNode* cur = Q.front();
        Q.pop();
        if (cur->left)
            Q.push(cur->left);
        if (cur->right)
            Q.push(cur->right);
        if (cur->right) {
            leftRight.push_back(cur->right->pos + cur->right->middle);
        } else {
            leftRight.push_back(cur->pos + cur->last);
        }
    }
    Q.push(node->right);
    while (!Q.empty() && rightLeft.size() < leftRight.size()) {
        InfoNode* cur = Q.front();
        Q.pop();
        int size = Q.size();
        if (cur->left)
            Q.push(cur->left);
        if (cur->right)
            Q.push(cur->right);
        while (size--) {
            InfoNode* cur = Q.front();
            Q.pop();
            if (cur->left)
                Q.push(cur->left);
            if (cur->right)
                Q.push(cur->right);
        }
        if (cur->left) {
            rightLeft.push_back(cur->left->pos + cur->left->middle);
        } else {
            rightLeft.push_back(cur->pos);
        }
    }
    const int minSpace = 1;
    int       cross    = 0;
    for (int i = 0; i < rightLeft.size(); i++) {
        int tmp = leftRight[i] + minSpace - rightLeft[i] + 1;
        cross   = tmp > cross ? tmp : cross;
    }
    return cross;
}

void Printer::movePos(InfoNode* node, int len) {
    if (node->left)
        this->movePos(node->left, len);
    if (node->right)
        this->movePos(node->right, len);
    node->pos += len;
}

std::ostream& operator<<(std::ostream& os, Printer& tree) {
    tree.initTreeStructure();
    if (tree.root == nullptr)
        return os;
    tree.setLayerLink();
    tree.initPosInfo();
    tree.agjustPosInfo();

    std::stringstream ss;

    for (auto cur : tree.layerHead) {
        int idx = 0;
        ss.str("");
        while (cur) {
            if (cur->left) {
                int limit = cur->left->pos + cur->left->middle;
                while (idx < limit) {
                    os << ' ';
                    ss << ' ';
                    idx++;
                }
                os << "┌";
                ss << "│";
                idx++;
                limit = cur->pos;
                while (idx < limit) {
                    os << "─";
                    ss << ' ';
                    idx++;
                }
            } else {
                int limit = cur->pos;
                while (idx < limit) {
                    os << ' ';
                    ss << ' ';
                    idx++;
                }
            }
            if (cur->isred) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            }
            os << cur->content;
            if (cur->isred) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            int limit = cur->pos + cur->last + 1;
            while (idx < limit) {
                ss << ' ';
                idx++;
            }
            if (cur->right) {
                int limit = cur->right->pos + cur->right->middle;
                while (idx < limit) {
                    os << "─";
                    ss << ' ';
                    idx++;
                }
                os << "┐";
                ss << "│";
                idx++;
            }
            cur = cur->next;
        }
        os << '\n'
           << ss.str() << '\n';
    }
    return os;
}
