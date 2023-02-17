#ifndef __HUFFMAN_TREE_HPP__
#define __HUFFMAN_TREE_HPP__

#include <unordered_map>
#include <string>
#include <queue>
#include <functional>
using namespace std;

using uint = unsigned int;

class HuffmanTree {
public:
    HuffmanTree();
    ~HuffmanTree();

public:
    // 创建哈夫曼树
    void create(const string& str);
    // 输出哈夫曼编码
    void huffmanCode();
    // 编码
    string encode(const string& str);
    // 解码
    string decode(const string& str);

private:
    struct Node {
        Node(char data, uint weight)
            : data_(data)
            , weight_(weight)
            , left_(nullptr)
            , right_(nullptr) { }

        char  data_;
        uint  weight_; // 节点的权值
        Node* left_;
        Node* right_;
    };

private:
    // 获取哈夫曼编码
    void getHuffmanCode();
    void getHuffmanCode(Node* node, string code);

private:
    Node* root_;
    // 存储字符对应的哈夫曼编码
    unordered_map<char, string> codeMap_;

    using MinHeap = priority_queue<Node*, vector<Node*>, function<bool(Node*, Node*)>>;
    MinHeap minHeap_;
};

#endif // !__HUFFMAN_TREE_HPP__