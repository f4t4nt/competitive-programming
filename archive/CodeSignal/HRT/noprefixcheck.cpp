#include "bits/stdc++.h"

using namespace std;

struct Trie {
    char c;
    int cnt = 0;
    bool end = false;
    vector<Trie*> children = vector<Trie*>(10, nullptr);

    Trie (char c) : c(c) {}

    bool insert(int i, string &s) {
        cnt++;
        if (i == s.size()) {
            end = true;
            return cnt == 1;
        } else if (end) {
            return false;
        }

        int si = s[i] - '0';
        if (children[si] == nullptr) {
            children[si] = new Trie(s[i]);
        }
        return children[si]->insert(i + 1, s);
    }
};

bool solution(vector<string> numbers) {
    Trie trie(' ');
    for (string s : numbers) {
        if (!trie.insert(0, s)) {
            return false;
        }
    }
    return true;
}
