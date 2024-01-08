#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;
 
#include <bits/extc++.h>
using namespace __gnu_pbds;
 
using indexed_set = tree<
    pair<ll, ll>,
    null_type,
    less<pair<ll, ll>>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;
 
#pragma GCC target("popcnt,lzcnt")
 
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

// <length, bit>

struct SegTree {
    ll n;
    vector<pair<ll, ll>> pre, suf, mx;
    SegTree (ll n) : n(n), pre(4 * n), suf(4 * n), mx(4 * n) {}
    void update(ll idx, ll val, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n;
        if (idx < l || r <= idx) return;
        if (r - l == 1) {
            pre[i] = suf[i] = mx[i] = {1, val};
            return;
        }
        ll m = (l + r) / 2, len_l = m - l, len_r = r - m;
        update(idx, val, 2 * i, l, m);
        update(idx, val, 2 * i + 1, m, r);
        if (pre[2 * i].first == len_l && pre[2 * i].second == pre[2 * i + 1].second) {
            pre[i] = {pre[2 * i].first + pre[2 * i + 1].first, pre[2 * i].second};
        } else {
            pre[i] = pre[2 * i];
        }
        if (suf[2 * i + 1].first == len_r && suf[2 * i + 1].second == suf[2 * i].second) {
            suf[i] = {suf[2 * i + 1].first + suf[2 * i].first, suf[2 * i].second};
        } else {
            suf[i] = suf[2 * i + 1];
        }
        mx[i] = max({pre[i], suf[i], mx[2 * i], mx[2 * i + 1]});
        if (suf[2 * i].second == pre[2 * i + 1].second) {
            mx[i] = max({mx[i], {suf[2 * i].first + pre[2 * i + 1].first, suf[2 * i].second}});
        }
    }
    void print_tree(ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n;
        cout << "i: " << i << " [" << l << ", " << r << ")\n";
        cout << "pre: <len: " << pre[i].first << ", bit: " << pre[i].second << ">\n";
        cout << "suf: <len: " << suf[i].first << ", bit: " << suf[i].second << ">\n";
        cout << "mx: <len: " << mx[i].first << ", bit: " << mx[i].second << ">\n";
        if (r - l == 1) return;
        ll m = (l + r) / 2;
        print_tree(2 * i, l, m);
        print_tree(2 * i + 1, m, r);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    str s;
    cin >> s;
    ll n = sz(s), t;
    cin >> t;
    SegTree st(n);
    FOR (i, n) {
        st.update(i, s[i] - '0');
    }
    while (t--) {
        ll x;
        cin >> x;
        x--;
        s[x] = (s[x] == '0' ? '1' : '0');
        st.update(x, s[x] - '0');
        // cout << s << '\n';
        // st.print_tree();
        // cout << '\n';
        cout << st.mx[1].first << ' ';
    }
    cout << '\n';

    return 0;
}