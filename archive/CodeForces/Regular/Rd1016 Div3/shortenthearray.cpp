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
    ll,
    null_type,
    less<ll>,
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
// #define f first
// #define s second

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

struct Trie {
    ll c, val = 0, lvl, prv = -1e18;
    Trie* children[2] = {nullptr};

    Trie(ll c, ll val) : c(c), val(val) {}

    void insert(ll i, ll idx, ll x) {
        lvl = i, prv = idx;
        if (i == -1) return;
        ll xi = (x >> i) & 1;
        if (children[xi] == nullptr)
            children[xi] = new Trie(c, val | (xi << i));
        children[xi]->insert(i - 1, idx, x);
    }

    ll query(ll i, ll x, ll k) {
        if (i == -1) return prv;
        ll xi = (x >> i) & 1, ki = (k >> i) & 1, ans = -1e18;
        if (!xi && !ki) {
            if (children[1] != nullptr)
                ans = children[1]->prv;
            if (children[0] != nullptr)
                ans = max(ans, children[0]->query(i - 1, x, k));
        }
        if (xi && !ki) {
            if (children[0] != nullptr)
                ans = children[0]->prv;
            if (children[1] != nullptr)
                ans = max(ans, children[1]->query(i - 1, x, k));
        }
        if (!xi && ki && children[1] != nullptr)
            ans = children[1]->query(i - 1, x, k);
        if (xi && ki && children[0] != nullptr)
            ans = children[0]->query(i - 1, x, k);
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n, k; cin >> n >> k;
        vector<ll> a(n);
        for (ll &ai : a) cin >> ai;
        ll ans = 1e9;
        Trie* root = new Trie(0, 0);
        for (ll i = 0; i < n; i++) {
            root->insert(32, i, a[i]);
            ans = min(ans, i - root->query(32, a[i], k) + 1);
        }
        cout << (ans == 1e9 ? -1 : ans) << '\n';
    }

    return 0;
}