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

// struct SegTree {
//     ll n; vector<ll> data, lazy;
//     SegTree (ll n) : n(n), data(4 * n), lazy(4 * n) {}
//     void push(ll i, ll l, ll r) {
//         data[i] += (r - l) * lazy[i];
//         if (r - l > 1) {
//             lazy[2 * i] += lazy[i];
//             lazy[2 * i + 1] += lazy[i];
//         }
//         lazy[i] = 0;
//     }
//     void upd(ll ul, ll ur, ll val, ll i = 1, ll l = 0, ll r = -1) { // [ul, ur)
//         if (r == -1) r = n; push(i, l, r);
//         if (ur <= l || r <= ul) return;
//         if (ul <= l && r <= ur) {
//             lazy[i] += val;
//             push(i, l, r);
//             return;
//         }
//         ll m = (l + r) / 2;
//         upd(ul, ur, val, 2 * i, l, m);
//         upd(ul, ur, val, 2 * i + 1, m, r);
//         data[i] = data[2 * i] + data[2 * i + 1];
//     }
//     ll qry(ll ql, ll qr, ll i = 1, ll l = 0, ll r = -1) {
//         if (r == -1) r = n; push(i, l, r);
//         if (qr <= l || r <= ql) return 0;
//         if (ql <= l && r <= qr) return data[i];
//         ll m = (l + r) / 2;
//         return qry(ql, qr, 2 * i, l, m) + qry(ql, qr, 2 * i + 1, m, r);
//     }
// };

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, m; cin >> n >> m;
    vector<ll> r(n);
    FOR (i, n) cin >> r[i];
    // SegTree st(m + 1);
    // ll cur = 0;

    // FOR (j, m + 1) {
    //     cerr << st.qry(j, j + 1) << ' ';
    //     if (j == cur) cerr << "| ";
    // }
    // cerr << '\n';

    // FOR (i, n) {
    //     ll q = r[i];
    //     if (q == 0) {
    //         ll prv = st.qry(cur, cur + 1);
    //         cur++;
    //         st.upd(cur, cur + 1, prv);
    //     } elif (q < 0) {
    //         q = -q;
    //         ll ur = cur - q + 1;
    //         if (0 < ur) st.upd(0, ur, 1);
    //     } else {
    //         ll ur = cur + 1;
    //         if (q < ur) st.upd(q, ur, 1);
    //     }

    //     FOR (j, m + 1) {
    //         cerr << st.qry(j, j + 1) << ' ';
    //         if (j == cur) cerr << "| ";
    //     }
    //     cerr << '\n';
    // }
    // vector<ll> res(m + 1);
    // FOR (i, m + 1) res[i] = st.qry(i, i + 1);
    // cout << *max_element(all(res)) << '\n';

    ll pts = 0;
    map<ll, ll> cutoff;
    FOR (i, n) {
        ll q = r[i];
        if (q == 0) {
            pts++;
            map<ll, ll> tmp;
            for (auto [k, v] : cutoff) {
                if (v < 0) tmp[k + 1] += v;
                else tmp[k] += v;
            }
            swap(cutoff, tmp);
        } elif (q < 0) {
            q = -q;
            ll hi = pts - q + 1;
            if (0 < hi) {
                cutoff[0]++;
                cutoff[hi]--;
            }
        } else {
            ll hi = pts + 1;
            if (q < hi) {
                cutoff[q]++;
                cutoff[hi]--;
            }
        }
        // ll idx = 0, cur = 0;
        // while (idx <= m) {
        //     cur += cutoff[idx];
        //     cerr << cur << ' ';
        //     if (idx++ == pts) cerr << "| ";
        // }
        // cerr << '\n';
    }
    ll res = 0, cur = 0;
    for (auto [k, v] : cutoff) {
        cur += v;
        res = max(res, cur);
    }
    cout << res << '\n';

    return 0;
}