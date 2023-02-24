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
#define mp make_pair
#define mt make_tuple
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for(ll x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FOI(x, e, i) for(ll x = 0; x < (ll) e; x += (ll) i)
#define FOBI(x, b, e, i) for(ll x = (ll) b; x < (ll) e; x += (ll) i)
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

constexpr ll MOD = 1e9 + 7;
constexpr ll ALPHA = 26;

struct Trie {
    ch c;
    bool ending = false;
    vector<Trie*> children = vector<Trie*>(ALPHA, nullptr);

    Trie(ch c_) : c(c_) {}

    void insert(ll i, str &s) {
        if (i == sz(s)) {
            ending = true;
            return;
        }
        ll si = s[i] - 'a';
        if (children[si] == nullptr) {
            children[si] = new Trie(s[i]);
        }
        children[si]->insert(i + 1, s);
    }

    void search(ll i, ll len, str &s, vector<ll> &dp) {
        if (ending) {
            dp[i] = (dp[i] + dp[i - len]) % MOD;
        }
        if (i == sz(s)) {
            return;
        }
        if (children[s[i] - 'a'] != nullptr) {
            children[s[i] - 'a']->search(i + 1, len + 1, s, dp);
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    str s;
    cin >> s;
    Trie tri('$');
    ll k;
    cin >> k;
    vector<str> words(k);
    FOR (i, k) {
        cin >> words[i];
        tri.insert(0, words[i]);
    }

    vector<ll> dp(sz(s) + 1, 0);
    dp[0] = 1;
    FOR (i, sz(s)) {
        tri.search(i, 0, s, dp);
    }
    cout << dp[sz(s)] << '\n';

    return 0;
}