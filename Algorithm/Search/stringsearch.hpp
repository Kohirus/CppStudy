#ifndef __STRING_SEARCH_HPP__
#define __STRING_SEARCH_HPP__

#include <string>
using namespace std;

// BF算法
int bruteForce(const string& s, const string& t) {
    int i = 0, j = 0;
    while (i < s.size() && j < t.size()) {
        if (s[i] == t[j]) {
            i++;
            j++;
        } else {
            // 将i回退到之前匹配的起始位置的下一个字符
            i = i - j + 1;
            j = 0;
        }
    }

    return (j == t.size()) ? (i - j) : -1;
}

// 计算模式串的next数组
vector<int> getNext(const string& str) {
    vector<int> next(str.size(), -1);
    // j用来遍历字符串 k表示公共前后缀的长度
    int j = 0, k = -1;
    while (j < str.size() - 1) {
        if (k == -1 || str[k] == str[j]) {
            j++;
            k++;

            // 算法优化
            if (str[k] == str[j]) {
                next[j] = next[k];
            } else {
                next[j] = k;
            }
        } else {
            k = next[k];
        }
    }
    return next;
}

// KMP算法
int kmp(const string& s, const string& t) {
    int i = 0, j = 0;

    vector<int> next = getNext(t);

    while (i < s.size() && j < static_cast<int>(t.size())) {
        if (j == -1 || s[i] == s[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
    }

    return (j == t.size()) ? (i - j) : -1;
}

#endif // !__STRING_SEARCH_HPP__