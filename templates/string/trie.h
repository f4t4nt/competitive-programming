#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef string str;
typedef char ch;

const ll ALPHA = 26;

// -----------------------------------------------------------------------------
//  Trie
// -----------------------------------------------------------------------------
//  Supports:   - insert(s), contains(s), has_prefix(s)
//              - walk(s)  node reached by following s, nullptr if it
//                falls off
//  Restrictions: - lowercase 'a'..'z'; widen ALPHA for more
//  Complexity: O(|s|) per operation
// -----------------------------------------------------------------------------
struct Trie {
    bool ending = false;                                   // some inserted word ends here
    vector<Trie*> child = vector<Trie*>(ALPHA, nullptr);   // child[c - 'a']

    // insert s below this node
    void insert(str &s) {
        Trie *cur = this;
        for (ch c : s) {
            ll i = c - 'a';
            if (!cur->child[i]) cur->child[i] = new Trie();
            cur = cur->child[i];
        }
        cur->ending = true;
    }

    // follow s from this node; nullptr if it falls off
    Trie *walk(str &s) {
        Trie *cur = this;
        for (ch c : s) {
            cur = cur->child[c - 'a'];
            if (!cur) return nullptr;
        }
        return cur;
    }

    // queries
    bool contains(str &s) { Trie *v = walk(s); return v != nullptr && v->ending; }
    bool has_prefix(str &s) { return walk(s) != nullptr; }
};
