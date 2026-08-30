#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maximum69Number (int num) {
        string tmp = to_string(num);
        for (int i = 0; i < tmp.size(); i++) {
            if (tmp[i] == '6') {
                tmp[i] = '9';
                break;
            }
        }
        return stoi(tmp);
    }
};
