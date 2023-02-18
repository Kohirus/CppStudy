#include "digraph.hpp"
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

void Digraph::readFile(const string& filePath) {
    FILE* pf = fopen(filePath.c_str(), "r");
    if (pf == nullptr) {
        throw filePath + " not exist!";
    }

    // 占用第0号位置
    vertics.emplace_back("");

    while (!feof(pf)) {
        char line[1024] = { 0 };
        fgets(line, 1024, pf);
        // 增加一个节点信息
        string linestr(line);
        vertics.emplace_back(linestr.substr(0, linestr.size() - 1));

        fgets(line, 1024, pf);
        char* vertic_no = strtok(line, ",");
        while (vertic_no != nullptr) {
            int vex = atoi(vertic_no);
            if (vex > 0) {
                vertics.back().adjList_.emplace_back(vex);
            }
            vertic_no = strtok(nullptr, ",");
        }
    }
}

void Digraph::show() const {
    for (int i = 1; i < vertics.size(); ++i) {
        cout << vertics[i].data_ << " : ";
        for (auto& no : vertics[i].adjList_) {
            cout << no << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void Digraph::dfs() {
    vector<bool> visited(vertics.size(), false);
    dfs(1, visited);
    cout << endl;
}

void Digraph::bfs() {
    vector<bool> visited(vertics.size(), false);
    queue<int>   que;
    que.push(1);
    visited[1] = true;
    while (!que.empty()) {
        int cur_no = que.front();
        que.pop();

        cout << vertics[cur_no].data_ << " ";
        for (auto& no : vertics[cur_no].adjList_) {
            if (!visited[no]) {
                que.push(no);
                visited[no] = true;
            }
        }
    }
}

void Digraph::dfs(int start, vector<bool>& visited) {
    if (visited[start]) return;

    cout << vertics[start].data_ << " ";
    visited[start] = true;

    // 递归遍历下一层节点
    for (auto& no : vertics[start].adjList_) {
        dfs(no, visited);
    }
}