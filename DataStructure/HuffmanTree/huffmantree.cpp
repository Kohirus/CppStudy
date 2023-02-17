#include "huffmantree.hpp"
#include <iostream>
#include <queue>

HuffmanTree::HuffmanTree()
    : root_(nullptr)
    , minHeap_([](Node* n1, Node* n2) -> bool {
        return n1->weight_ > n2->weight_;
    }) {
}

HuffmanTree::~HuffmanTree() {
    if (root_ != nullptr) {
        queue<Node*> qe;
        qe.push(root_);
        while (!qe.empty()) {
            Node* front = qe.front();
            qe.pop();
            if (front->left_)
                qe.push(front->left_);
            if (front->right_)
                qe.push(front->right_);
            delete front;
        }
        root_ = nullptr;
    }
}

void HuffmanTree::create(const string& str) {
    // 先统计字符的权值
    unordered_map<char, uint> dataMap;
    for (char ch : str) {
        dataMap[ch]++;
    }

    // 生成节点 放入小根堆中
    for (auto& pair : dataMap) {
        minHeap_.push(new Node(pair.first, pair.second));
    }

    while (minHeap_.size() > 1) {
        // 取出两个权值最小的节点
        Node* n1 = minHeap_.top();
        minHeap_.pop();

        Node* n2 = minHeap_.top();
        minHeap_.pop();

        // 生成父节点
        Node* node   = new Node('\0', n1->weight_ + n2->weight_);
        node->left_  = n1;
        node->right_ = n2;

        minHeap_.push(node);
    }

    root_ = minHeap_.top();
    minHeap_.pop();

    // 生成哈夫曼编码
    getHuffmanCode();
}

void HuffmanTree::huffmanCode() {
    for (auto& pair : codeMap_) {
        cout << pair.first << " : " << pair.second << endl;
    }
    cout << endl;
}

string HuffmanTree::encode(const string& str) {
    string res;
    for (char ch : str) {
        res.append(codeMap_[ch]);
    }
    return res;
}

string HuffmanTree::decode(const string& str) {
    string res;
    Node*  cur = root_;
    for (char ch : str) {
        if (ch == '0') {
            cur = cur->left_;
        } else {
            cur = cur->right_;
        }

        if (cur->left_ == nullptr && cur->right_ == nullptr) {
            res.push_back(cur->data_);
            cur = root_;
        }
    }
    return res;
}

void HuffmanTree::getHuffmanCode() {
    getHuffmanCode(root_, "");
}

void HuffmanTree::getHuffmanCode(Node* node, string code) {
    if (node->left_ == nullptr && node->right_ == nullptr) {
        codeMap_[node->data_] = code;
        return;
    }

    getHuffmanCode(node->left_, code + "0");
    getHuffmanCode(node->right_, code + "1");
}