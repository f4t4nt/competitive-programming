#include <bits/stdc++.h>
using namespace std;

typedef int ll;
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
#define sz(C) (ll)C.size()
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

struct SegTree {
    ll n; vector<ll> data, lazy;
    SegTree (ll n, vector<ll> &raw) : n(n), data(4 * n), lazy(4 * n)
        { build(raw); }
    ll build(vector<ll> &raw, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n;
        if (r - l == 1) return data[i] = raw[l];
        ll m = (l + r) / 2;
        return data[i] = max(build(raw, 2 * i, l, m), build(raw, 2 * i + 1, m, r));
    }
    void fill(vector<ll> &vec, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n; push(i, l, r);
        if (r - l == 1) vec[l] = data[i];
        else {
            ll m = (l + r) / 2;
            fill(vec, 2 * i, l, m);
            fill(vec, 2 * i + 1, m, r);
        }
        return;
    }
    void push(ll i, ll l, ll r) {
        data[i] = max(data[i], lazy[i]);
        if (r - l > 1) {
            lazy[2 * i] = max(lazy[2 * i], lazy[i]);
            lazy[2 * i + 1] = max(lazy[2 * i + 1], lazy[i]);
        }
        lazy[i] = 0;
    }
    void upd(ll ul, ll ur, ll val, ll i = 1, ll l = 0, ll r = -1) { // [ul, ur)
        if (r == -1) r = n; push(i, l, r);
        if (ur <= l || r <= ul) return;
        if (ul <= l && r <= ur) {
            lazy[i] = max(lazy[i], val);
            push(i, l, r);
            return;
        }
        ll m = (l + r) / 2;
        upd(ul, ur, val, 2 * i, l, m);
        upd(ul, ur, val, 2 * i + 1, m, r);
        data[i] = max(data[2 * i], data[2 * i + 1]);
    }
    ll qry(ll ql, ll qr, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n; push(i, l, r);
        if (qr <= l || r <= ql) return 0;
        if (ql <= l && r <= qr) return data[i];
        ll m = (l + r) / 2;
        return max(qry(ql, qr, 2 * i, l, m), qry(ql, qr, 2 * i + 1, m, r));
    }
};

void eval(ll i, ll k, vector<ll> &last, SegTree &st) {
    set<ll> last_set(all(last));
    last_set.insert(0);
    bitset<1 << 17> seen;
    for (ll x : last_set) {
        for (ll add = -1; add <= 2; add++) {
            ll start = x + add;
            if (start >= 0 && start <= i) {
                ll cur = 0;
                for (ll j = 0; j < k; j++) {
                    ll xx = last[j];
                    if (xx > start) xx--;
                    if (xx < start) xx = start - 1;
                    if ((i - xx) % 2 == 0) cur |= 1 << j;
                }
                if (!seen[cur]) {
                    st.upd(start, i + 1, cur);
                    seen[cur] = 1;
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n, k; cin >> n >> k;
        vector<ll> a(n);
        for (ll &ai : a) cin >> ai;
        SegTree st(n, a);

        vector<ll> last(k, -1);
        for (ll i = 0; i < n; i++) {
            for (ll j = 0; j < k; j++)
                if ((a[i] >> j) & 1)
                    last[j] = i;
            eval(i, k, last, st);
        }

        vector<ll> ans(n);
        st.fill(ans);
        for (ll x : ans) cout << x << ' ';
        cout << '\n';
    }

    return 0;
}