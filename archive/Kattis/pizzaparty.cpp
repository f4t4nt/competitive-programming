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
    pair<ll, ll>,
    null_type,
    less<pair<ll, ll>>,
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

ll get_id(str s, map<str, ll> &ids) {
    if (!ids.count(s)) ids[s] = sz(ids);
    return ids[s];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    str line; getline(cin, line);
    ll n = stoll(line);
    map<str, ll> ids;
    vector<bool> vis(5e5);
    vector<vector<ll>> adj(5e5);
    map<ll, vector<vector<ll>>> ands;
    queue<ll> q;
    FOR (i, n) {
        getline(cin, line);
        istringstream iss(line);
        str cur;
        vector<str> words;
        while (iss >> cur) words.pb(cur);
        if (sz(words) == 1) { // [topping]
            vis[get_id(words[0], ids)] = true;
            q.push(get_id(words[0], ids));
            ands.erase(get_id(words[0], ids));
        } elif (sz(words) == 4) { // if [topping1] then [topping2]
            ll u = get_id(words[1], ids);
            ll v = get_id(words[3], ids);
            adj[u].pb(v);
        } elif (words[2] == "or") { // if [topping1] or [topping2] or ... then [topping3]
            vector<ll> us;
            for (ll i = 1; i < sz(words) - 1; i += 2) us.pb(get_id(words[i], ids));
            ll v = get_id(words.back(), ids);
            FORE (u, us) adj[u].pb(v);
        } elif (words[2] == "and") { // if [topping1] and [topping2] and ... then [topping3]
            vector<ll> us;
            for (ll i = 1; i < sz(words) - 1; i += 2) us.pb(get_id(words[i], ids));
            ll v = get_id(words.back(), ids);
            ands[v].pb(us);
        } else assert(false);
    }
    cout << '\n';
    while (!q.empty()) {
        while (!q.empty()) {
            ll u = q.front(); q.pop();
            FORE (v, adj[u]) {
                if (!vis[v]) {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
        vector<ll> nv;
        for (auto [v, cond] : ands) {
            if (vis[v]) continue;
            FORE (us, cond) {
                bool ok = true;
                FORE (u, us) {
                    if (!vis[u]) {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    vis[v] = true;
                    q.push(v);
                    nv.pb(v);
                    break;
                }
            }
        }
        FORE (v, nv) ands.erase(v);
    }
    ll rv = accumulate(all(vis), 0LL);
    cout << rv << '\n';

    return 0;
}