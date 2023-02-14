#include <iostream>
#include <string>
#include <vector>
#include "trie.hpp"
using namespace std;

int main() {
    TrieTree tree;
    tree.add("hello");
    tree.add("hello");
    tree.add("happy");
    tree.add("helmet");
    tree.add("helmet");
    tree.add("world");
    tree.add("world");
    tree.add("world");
    tree.add("wonderfully");

    cout << "hello: " << tree.query("hello") << endl;
    cout << "happy: " << tree.query("happy") << endl;
    cout << "helmet: " << tree.query("helmet") << endl;
    cout << "world: " << tree.query("world") << endl;
    cout << "wonderfully: " << tree.query("wonderfully") << endl;
    cout << "====================" << endl;

    vector<string> wordlist = tree.allWords();
    for (auto word : wordlist) {
        cout << word << endl;
    }
    cout << "====================" << endl;

    wordlist = tree.queryPrefix("he");
    for (auto word : wordlist) {
        cout << word << endl;
    }
    cout << "====================" << endl;

    tree.add("he");
    tree.add("hellooo");
    tree.add("hellooo");
    wordlist = tree.allWords();
    for (auto word : wordlist) {
        cout << word << endl;
    }
    cout << "====================" << endl;

    tree.remove("he");
    tree.remove("hellooo");
    tree.remove("hellooo");
    wordlist = tree.allWords();
    for (auto word : wordlist) {
        cout << word << endl;
    }
    cout << "====================" << endl;

    return 0;
}