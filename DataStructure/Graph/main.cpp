#include <iostream>
#include "digraph.hpp"
using namespace std;

int main() {
    Digraph graph;
    graph.readFile("data.txt");
    graph.show();
    graph.dfs();
    graph.bfs();
    return 0;
}