#include <iostream>
#include "invertedindex.hpp"
using namespace std;

int main() {
    InvertIndex index;
    index.addSuffix(".cpp");
    index.addSuffix(".hpp");
    index.setSearchPath("D:\\Code\\VS Code\\CppStudy");

    for (;;) {
        cout << "===================" << endl;
        char buf[128] = { 0 };
        cout << "Search: ";
        cin.getline(buf, 128);

        index.query(buf);
    }

    return 0;
}