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

const ll INF = 1e18;

struct SegTree {
    ll n; vector<ll> data;
    SegTree (ll n, vector<ll> &raw) : n(n), data(4 * n, INF) { build(raw); }
    ll build(vector<ll> &raw, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n;
        if (r - l == 1) return data[i] = raw[l];
        ll m = (l + r) / 2;
        return data[i] = min(build(raw, 2 * i, l, m), build(raw, 2 * i + 1, m, r));
    }
    void upd(ll ui, ll val, ll i = 1, ll l = 0, ll r = -1) { // [ul, ur)
        if (r == -1) r = n;
        if (ui < l || r <= ui) return;
        if (ui == l && ui + 1 == r) {
            data[i] = val;
            return;
        }
        ll m = (l + r) / 2;
        upd(ui, val, 2 * i, l, m);
        upd(ui, val, 2 * i + 1, m, r);
        data[i] = min(data[2 * i], data[2 * i + 1]);
    }
    ll qry(ll ql, ll qr, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n;
        if (qr <= l || r <= ql) return INF;
        if (ql <= l && r <= qr) return data[i];
        ll m = (l + r) / 2;
        return min(qry(ql, qr, 2 * i, l, m), qry(ql, qr, 2 * i + 1, m, r));
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, tot_f = 0; cin >> n;
    vector<pll> components(n);
    FOR (i, n) {
        cin >> components[i].s >> components[i].f;
        tot_f = max(tot_f, components[i].s);
    }
    tot_f = tot_f * 2;
    ssort(components);
    vector<ll> ref(tot_f + 1, 0);
    for (auto [t, k] : components) {
        vector<ll> evens(tot_f + 1), odds = evens;
        FOR (i, tot_f + 1) {
            ll even = 0, odd = 0;
            if (2 * i <= tot_f) even = ref[2 * i];
            if (2 * i + 1 <= tot_f) odd = ref[2 * i + 1];
            evens[i] = even + t * i;
            odds[i] = odd + t * i;
        }
        SegTree evens_st(tot_f + 1, evens), odds_st(tot_f + 1, odds);
        ref = vector<ll>(tot_f + 1, t * k);
        FOR (i, tot_f + 1) {
            ll qr = i + k, len = min(i, k);
            if (qr % 2 == 0) {
                qr = min(tot_f, qr) / 2;
                ll ql = max(0LL, qr - len);
                ref[i] += evens_st.qry(ql, qr + 1) - qr * t;
            } else {
                qr = min(tot_f - 1, qr) / 2;
                ll ql = max(0LL, qr - len);
                ref[i] += odds_st.qry(ql, qr + 1) - qr * t;
            }
        }
    }
    cout << ref[0] << '\n';

    return 0;
}