#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;
 
#include <bits/extc++.h>
using namespace __gnu_pbds;
 
using indexed_set = tree<
    pair<ll, ll>,
    null_type,
    less<pair<ll, ll>>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;
 
#pragma GCC target("popcnt,lzcnt")
 
#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
 
#define FOR(x, e) for(ll x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FORE(x, C) for(auto &x : C)
 
#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

str collapse(str a, str b) {
    if (a.empty()) return b;
    if (b.empty()) return a;
    if (a.back() == b.front()) {
        a.pop_back();
        return collapse(a, b.substr(1));
    }
    return a + b;
}

ll brute(vector<str> &s) {
    ll rv = 0;
    FORE (a, s) {
        FORE (b, s) {
            rv += sz(collapse(a, b));
        }
    }
    return rv;
}

constexpr ll ALPHA = 26;

struct Trie {
    ch c;
    ll cnt = 0;
    bool ending = false;
    vector<Trie*> children = vector<Trie*>(ALPHA, nullptr);

    Trie(ch c_) : c(c_) {}

    void insert(ll i, str &s) {
        cnt++;
        if (i == sz(s)) {
            ending = true;
            return;
        }
        ll j = s[i] - 'a';
        if (children[j] == nullptr) {
            children[j] = new Trie(s[i]);
        }
        children[j]->insert(i + 1, s);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, total = 0, rv = 0;
    cin >> n;
    vector<str> s(n);
    Trie trie(' ');
    FOR (i, n) {
        cin >> s[i];
        total += sz(s[i]);
        trie.insert(0, s[i]);
    }
    FORE (a, s) {
        rv += total + sz(a) * n;
        auto node = &trie;
        FORR (i, sz(a)) {
            ll idx = a[i] - 'a';
            if (node->children[idx] == nullptr) {
                break;
            }
            node = node->children[idx];
            rv -= node->cnt * 2;
        }
    }
    cout << rv << '\n';

    return 0;
}