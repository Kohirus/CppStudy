#include "trie.hpp"
#include <queue>

TrieTree::TrieTree() {
    root_ = new TrieNode('\0', 0);
}

TrieTree::~TrieTree() {
    destory(root_);
}

void TrieTree::add(const string& word) {
    TrieNode* cur = root_;

    for (int i = 0; i < word.size(); i++) {
        auto childIter = cur->nodeMap_.find(word[i]);
        if (childIter == cur->nodeMap_.end()) {
            // 相应字符的节点不存在 创建之
            TrieNode* child = new TrieNode(word[i], 0);
            cur->nodeMap_.emplace(word[i], child);
            cur = child;
        } else {
            // 相应节点已经存在
            cur = childIter->second;
        }
    }

    // 此时cur指向该单词的最后一个节点
    cur->freqs_++;
}

void TrieTree::remove(const string& word) {
    TrieNode *cur = root_, *del = root_;
    char      delch = word[0];

    for (int i = 0; i < word.size(); ++i) {
        auto iter = cur->nodeMap_.find(word[i]);
        if (iter == cur->nodeMap_.end()) {
            return;
        }

        // 遇到了另一个比较短的单词
        if (cur->freqs_ > 0 || cur->nodeMap_.size() > 1) {
            del   = cur;
            delch = word[i];
        }

        cur = iter->second;
    }

    // word单词存在
    if (cur->nodeMap_.empty()) {
        TrieNode* child = del->nodeMap_[delch];
        del->nodeMap_.erase(delch);
        destory(child);
    } else {
        // 当前删除节点之后还存在其它字符 不能直接删除
        cur->freqs_ = 0;
    }
}

int TrieTree::query(const string& word) {
    TrieNode* cur = root_;
    for (int i = 0; i < word.size(); ++i) {
        auto iter = cur->nodeMap_.find(word[i]);
        if (iter == cur->nodeMap_.end()) {
            return 0;
        }
        cur = iter->second;
    }

    return cur->freqs_;
}

vector<string> TrieTree::allWords() {
    vector<string> res;
    preOrder(root_, res, "");
    return res;
}

void TrieTree::preOrder(TrieNode* node, vector<string>& vec, string word) {
    if (node != root_) {
        word.push_back(node->ch_);
        if (node->freqs_ > 0) {
            // 已经遍历到一个有效的单词
            vec.emplace_back(word);
        }
    }

    // 递归处理孩子节点
    for (auto pair : node->nodeMap_) {
        preOrder(pair.second, vec, word);
    }
}

vector<string> TrieTree::queryPrefix(const string& prefix) {
    TrieNode* cur = root_;
    for (int i = 0; i < prefix.size(); ++i) {
        auto iter = cur->nodeMap_.find(prefix[i]);
        if (iter == cur->nodeMap_.end()) {
            return {};
        }
        cur = iter->second;
    }

    // 此时cur指向前缀的最后一个字符
    vector<string> res;
    preOrder(cur, res, prefix.substr(0, prefix.size() - 1));
    return res;
}

void TrieTree::destory(TrieNode* node) {
    queue<TrieNode*> qe;
    qe.push(node);
    while (!qe.empty()) {
        TrieNode* cur = qe.front();
        qe.pop();
        for (auto& pair : cur->nodeMap_) {
            qe.push(pair.second);
        }
        delete cur;
    }
}