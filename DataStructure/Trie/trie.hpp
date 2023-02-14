#ifndef __TRIE_HPP__
#define __TRIE_HPP__

#include <string>
#include <map>
#include <vector>
using namespace std;

class TrieTree {
public:
    TrieTree();
    ~TrieTree();

public:
    // 添加单词
    void add(const string& word);
    // 删除单词
    void remove(const string& word);
    // 查询单词的频率
    int query(const string& word);
    // 按字母表顺序获取所有的单词
    vector<string> allWords();
    // 前缀搜索
    vector<string> queryPrefix(const string& prefix);

private:
    // 节点类型
    struct TrieNode {
        TrieNode(char ch, int freqs)
            : ch_(ch)
            , freqs_(freqs) { }
        char ch_;    // 节点存储的字符
        int  freqs_; // 单词出现的频率
        // 存储孩子节点字符数据和节点指针的映射关系
        map<char, TrieNode*> nodeMap_;
    };

    // 递归前序遍历字典树
    void preOrder(TrieNode* node, vector<string>& vec, string word);
    // 删除节点
    void destory(TrieNode* node);

    TrieNode* root_;
};

#endif // !__TRIE_HPP__