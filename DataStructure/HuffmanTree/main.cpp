#include <iostream>
#include "huffmantree.hpp"
using namespace std;

int main() {
    HuffmanTree tree;
    string      str = "ABACDAEFDEG";
    tree.create(str);
    tree.huffmanCode();
    string res = tree.encode(str);
    cout << "encode: " << res << endl;
    cout << "decode: " << tree.decode(res);
    return 0;
}