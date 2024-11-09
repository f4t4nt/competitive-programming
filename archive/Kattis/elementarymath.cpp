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
// #define x first
// #define y second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FOR1(x, e) for (ll x = 1; x <= (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

ll get_id(map<ll, ll> &res, ll k, vector<ll> &ref) {
    if (!res.count(k)) {
        res[k] = sz(res);
        ref.pb(k);
    }
    return res[k];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n; cin >> n;
    vector<ll> ref_id;
    map<ll, ll> res_id;
    vector<pair<ll, ll>> edges, qs;
    FOR (i, n) {
        ll a, b; cin >> a >> b;
        qs.pb({a, b});
        edges.pb({i, get_id(res_id, a + b, ref_id)});
        edges.pb({i, get_id(res_id, a - b, ref_id)});
        edges.pb({i, get_id(res_id, a * b, ref_id)});
    }

    vector<vector<ll>> adj(n);
    for (auto &[u, v] : edges) adj[u].pb(v);

    ll rhs_cnt = sz(ref_id);
    vector<ll> matching(rhs_cnt, -1);
    vector<bool> vis_lhs(n), vis_rhs(rhs_cnt);

    FOR (u, n) {
        for (ll v : adj[u]) {
            if (matching[v] == -1) {
                matching[v] = u;
                vis_lhs[u] = true;
                break;
            }
        }
    }

    function<bool(ll)> bpm = [&](ll u) {
        for (ll v : adj[u]) {
            if (!vis_rhs[v]) {
                vis_rhs[v] = true;
                if (matching[v] == -1 || bpm(matching[v])) {
                    matching[v] = u;
                    return true;
                }
            }
        }
        return false;
    };

    FOR (u, n) if (!vis_lhs[u]) {
        fill(all(vis_rhs), false);
        bpm(u);
    }

    ll match_cnt = 0;
    FOR (u, rhs_cnt) if (matching[u] != -1) match_cnt++;

    if (match_cnt < n) {
        cout << "impossible" << endl;
        return 0;
    }

    vector<char> op(n);
    vector<ll> result(n);
    for (ll v = 0; v < rhs_cnt; v++) {
        if (matching[v] != -1) {
            ll u = matching[v];
            ll a = qs[u].first;
            ll b = qs[u].second;
            ll res_val = ref_id[v];
            if (a + b == res_val) {
                op[u] = '+';
                result[u] = res_val;
            } else if (a - b == res_val) {
                op[u] = '-';
                result[u] = res_val;
            } else if (a * b == res_val) {
                op[u] = '*';
                result[u] = res_val;
            } else {
                cout << "impossible" << endl;
                return 0;
            }
        }
    }

    for (ll i = 0; i < n; i++) {
        ll a = qs[i].first;
        ll b = qs[i].second;
        ll res_val = result[i];
        cout << a << " " << op[i] << " " << b << " = " << res_val << endl;
    }

    return 0;
}