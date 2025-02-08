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
#define f first
#define s second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FOR1(x, e) for (ll x = 1; x < (ll)e; x++)
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

const ll MOD = 1e9 + 7;
vector<ll> pow26 = {1};

struct SegTree {
    ll n; vector<pll> data;
    SegTree (ll n, vector<ll> &raw) : n(n), data(4 * n) { build(raw); }
    ll build(vector<ll> &raw, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n;
        if (r - l == 1) {
            data[i] = { raw[l], 1 };
            return data[i].f;
        }
        ll m = (l + r) / 2;
        data[i] = {
            (build(raw, 2 * i, l, m) + (build(raw, 2 * i + 1, m, r) * pow26[m - l]) % MOD) % MOD,
            r - l
        };
        return data[i].f;
    }
    void updi(ll ui, ll val, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n;
        if (r - l == 1) {
            data[i].f = val;
            return;
        }
        ll m = (l + r) / 2;
        if (ui < m) updi(ui, val, 2 * i, l, m);
        else updi(ui, val, 2 * i + 1, m, r);
        data[i].f = (data[2 * i].f + data[2 * i + 1].f * pow26[m - l] % MOD) % MOD;
    }
    pll qry(ll ql, ll qr, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n;
        if (qr <= l || r <= ql) return { 0, 0 };
        if (ql <= l && r <= qr) return data[i];
        ll m = (l + r) / 2;
        pll left = qry(ql, qr, 2 * i, l, m),
            right = qry(ql, qr, 2 * i + 1, m, r);
        ll combined_value = (left.f + right.f * pow26[left.s] % MOD) % MOD;
        ll combined_length = left.s + right.s;
        return { combined_value, combined_length };
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
 
    ll n, m; cin >> n >> m;
    FOR (i, n) pow26.pb(pow26.back() * 26 % MOD);

    str s; cin >> s;
    vector<ll> s_fwd(n), s_bwd(n);
    FOR (i, n) {
        s_fwd[i] = s[i] - 'a';
        s_bwd[i] = s[n - i - 1] - 'a';
    }

    SegTree fwd(n, s_fwd), bwd(n, s_bwd);
    while (m--) {
        ll q; cin >> q;
        if (q == 1) {
            ll k; ch c; cin >> k >> c; k--;
            fwd.updi(k, c - 'a');
            bwd.updi(n - k - 1, c - 'a');
            s_fwd[k] = c - 'a';
            s_bwd[n - k - 1] = c - 'a';
        } else {
            ll l, r; cin >> l >> r; l--, r--;
            ll fwd_hash = fwd.qry(l, r + 1).f;
            ll bwd_hash = bwd.qry(n - r - 1, n - l).f;
            cout << (fwd_hash == bwd_hash ? "YES" : "NO") << '\n';
        }
    }
 
    return 0;
}