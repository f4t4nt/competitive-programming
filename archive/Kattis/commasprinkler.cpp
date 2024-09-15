#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef complex<long double> cd;
typedef long double ld;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

using indexed_set = tree<
    pld,
    null_type,
    less<pld>,
    rb_tree_tag,
    tree_order_statistics_node_update>;

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
#define f first
#define s second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)
#define FOB(x, b, e) for (auto x = b; x < e; x++)
#define FORE(x, C) for (auto &x : C)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

str cut(str s) {
    if (s.back() == '.' || s.back() == ',') s.pop_back();
    return s;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    str line; getline(cin, line);
    istringstream iss(line);
    vector<str> words;
    map<str, ll> w2i;
    str word;
    while (iss >> word) {
        words.pb(word);
        word = cut(word);
        w2i[word] = sz(words) - 1;
    }
    ll n = sz(words), m = sz(w2i);
    // 2 * i = preceded by comma (when applicable)
    // 2 * i + 1 = postceded by comma (when applicable)
    vector<bool> states(2 * n);
    queue<ll> bfs;
    FOR (i, n - 1) if (words[i].back() == ',') {
        ll u = 2 * w2i[cut(words[i])], v = 2 * w2i[cut(words[i + 1])] + 1;
        states[u] = states[v] = 1;
        bfs.push(u), bfs.push(v);
    }
    vector<vector<ll>> adj(2 * n);
    FOR (i, n - 1) {
        str w1 = words[i], w2 = words[i + 1];
        if (w1.back() == '.') continue;
        w1 = cut(w1), w2 = cut(w2);
        ll u = 2 * w2i[w1], v = 2 * w2i[w2] + 1;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    while (sz(bfs)) {
        ll u = bfs.front(); bfs.pop();
        FORE (v, adj[u]) if (!states[v]) {
            states[v] = 1;
            bfs.push(v);
        }
    }
    FORE (w, words) {
        if (w.back() == '.' || w.back() == ',') cout << w << ' ';
        else {
            cout << w;
            if (states[2 * w2i[cut(w)]]) cout << ',';
            cout << ' ';
        }
    }
    cout << '\n';

    return 0;
}