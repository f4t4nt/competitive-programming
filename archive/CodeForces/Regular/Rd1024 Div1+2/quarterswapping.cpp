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

template<typename T>
using indexed_set = tree<
    T,
    null_type,
    less<T>,
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

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

ll parity(ll n, vector<ll> &v, vector<ll> &sortv) {
    ll m = sz(v);
    vector<ll> pos(n + 1);
    vector<ch> vis(m, 0);
    for (ll i = 0; i < m; i++) pos[sortv[i]] = i;
    ll cyc = 0;
    for (ll i = 0; i < m; i++) if (!vis[i]) {
        cyc++;
        ll j = i;
        while (!vis[j]) {
            vis[j] = 1;
            j = pos[v[j]];
        }
    }
    return (m - cyc) & 1;
}

vector<ll> join(vector<ll> &o, vector<ll> &e) {
    vector<ll> res;
    ll i = 0, j = 0;
    while (i < sz(o) || j < sz(e)) {
        if (i < sz(o)) res.pb(o[i++]);
        if (j < sz(e)) res.pb(e[j++]);
    }
    return res;
}

vector<ll> solve(ll n, vector<ll> &a) {
    if (n < 4) return a;
    vector<ll> o, e;
    for (ll i = 0; i < n; i++) (i & 1 ? e : o).pb(a[i]);
    auto sorto = o, sorte = e;
    ssort(sorto), ssort(sorte);
    if (parity(n, o, sorto) == parity(n, e,sorte))
        return join(sorto, sorte);

    auto swapp = [&](vector<ll>& vec, bool odd) -> vector<ll> {
        vector<ll> tmp = vec;
        swap(tmp[sz(tmp) - 2], tmp[sz(tmp) - 1]);
        return odd ? join(tmp, sorte) : join(sorto, tmp);
    };

    auto cand1 = swapp(sorto, true),
        cand2 = swapp(sorte, false);
    return min(cand1, cand2);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        vector<ll> a(n);
        for (ll &x : a) cin >> x;
        vector<ll> ans = solve(n, a);
        for (ll &x : ans) cout << x << ' ';
        cout << '\n';
    }

    return 0;
}
