#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ch = char;
using str = string;

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

constexpr ll ALPHA = 26;

struct Trie {
    ch c;
    bool ending = false;
    vector<ll> idxs;
    vector<Trie*> children = vector<Trie*>(ALPHA, nullptr);

    Trie(ch c_) : c(c_) {}

    void insert(ll i, ll idx, str &s) {
        idxs.pb(idx);
        if (i == sz(s)) {
            ending = true;
            return;
        }
        ll si = s[i] - 'a';
        if (children[si] == nullptr) {
            children[si] = new Trie(s[i]);
        }
        children[si]->insert(i + 1, idx, s);
    }
};

ll get_cnt(ll x, vector<ll> &vec) {
    return upper_bound(all(vec), x) - vec.begin();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    Trie *root = new Trie(' ');
    ll n, q;
    cin >> n;
    vector<str> words(n);
    map<str, ll> ref;
    FOR (i, n) {
        cin >> words[i];
        root->insert(0, i, words[i]);
        ref[words[i]] = i;
    }
    cin >> q;
    vector<str> queries(q);
    FOR (i, q) {
        cin >> queries[i];
        vector<Trie*> path;
        Trie *cur = root;
        ll j = 0;
        while (j < sz(queries[i])) {
            ll si = queries[i][j] - 'a';
            if (cur->children[si] == nullptr) {
                break;
            }
            cur = cur->children[si];
            path.pb(cur);
            j++;
        }
        ll rv;
        if (!ref.count(queries[i])) {
            rv = n;
            FOR (i, sz(path)) {
                rv += sz(path[i]->idxs);
            }
        } else {
            ll idx = ref[queries[i]];
            rv = idx + 1;
            FOR (i, sz(path)) {
                rv += get_cnt(idx, path[i]->idxs);
            }
        }
        cout << rv << '\n';
    }

    return 0;
}