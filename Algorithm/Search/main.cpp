#include <vector>
#include <iostream>
#include "binearysearch.hpp"
#include "stringsearch.hpp"
using namespace std;

// #define BS
// #define BF
#define KMP

int main() {
#ifdef BS
    vector<int> nums   = { 13, 21, 33, 37, 40, 48, 50, 51, 69, 73, 82 };
    int         target = 50;
    cout << binearySearch1(nums, target) << endl;
    cout << binearySearch2(nums, target) << endl;
    cout << binearySearch3(nums, 0, nums.size() - 1, target) << endl;
#endif // BS

#ifdef BF
    string s = "ababcabcacbab", t = "abcac";
    int    pos = bruteForce(s, t);
    cout << s << " - " << t << " : " << pos << endl;

    s = "ababcabacabab", t = "aba";
    pos = bruteForce(s, t);
    cout << s << " - " << t << " : " << pos << endl;

    s = "ababcabacabab", t = "abcax";
    pos = bruteForce(s, t);
    cout << s << " - " << t << " : " << pos << endl;
#endif // BF

#ifdef KMP
    string s = "ababcabcacbab", t = "abcac";
    int    pos = bruteForce(s, t);
    cout << s << " - " << t << " : " << pos << endl;

    s = "ababcabacabab", t = "aba";
    pos = bruteForce(s, t);
    cout << s << " - " << t << " : " << pos << endl;

    s = "ababcabacabab", t = "abcax";
    pos = bruteForce(s, t);
    cout << s << " - " << t << " : " << pos << endl;
#endif // BF
}