#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;
using ch = char;
using str = string;

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

constexpr ll MAXD = 1 << 20;
ll cnter = 0;
vector<ll> all_lo(MAXD), all_hi(MAXD), cnt(MAXD);

struct SegTree {
    ll n;
    vector<set<ll>> data, lazy;
    SegTree (ll n) :
        n(n),
        data(4 * n),
        lazy(4 * n) {}
    void update(ll lo, ll hi, set<ll> val, ll i = 1, ll l = 0, ll r = -1) { // [lo, hi)
        if (r == -1) r = n;
        if (!lazy[i].empty()) {
            data[i] = lazy[i];
            if (r - l > 1) {
                lazy[2 * i] = lazy[i];
                lazy[2 * i + 1] = lazy[i];
            }
            lazy[i] = {};
        }
        if (lo <= l && r <= hi) {
            data[i] = val;
            if (r - l > 1) {
                lazy[2 * i] = val;
                lazy[2 * i + 1] = val;
            }
            return;
        }
        if (r <= lo || hi <= l) return;
        ll m = (l + r) / 2;
        update(lo, hi, val, 2 * i, l, m);
        update(lo, hi, val, 2 * i + 1, m, r);
    }
    set<ll> query(ll idx, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n;
        if (!lazy[i].empty()) {
            data[i] = lazy[i];
            if (r - l > 1) {
                lazy[2 * i] = lazy[i];
                lazy[2 * i + 1] = lazy[i];
            }
            lazy[i] = {};
        }
        if (idx <= l && r <= idx + 1) return data[i];
        if (r <= idx || idx + 1 <= l) return {};
        ll m = (l + r) / 2;
        auto left = query(idx, 2 * i, l, m), right = query(idx, 2 * i + 1, m, r);
        left.insert(all(right));
        return left;
    }
    void eval(ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n;
        if (!lazy[i].empty()) {
            data[i] = lazy[i];
            if (r - l > 1) {
                lazy[2 * i] = lazy[i];
                lazy[2 * i + 1] = lazy[i];
            }
            lazy[i] = {};
        }
        if (r - l == 1) {
            all_lo[l] = *data[i].begin();
            all_hi[l] = *data[i].rbegin();
            FORE (x, data[i]) {
                if (cnt[x] == 0) cnt[x] = cnter++;
            }
            return;
        }
        ll m = (l + r) / 2;
        eval(2 * i, l, m);
        eval(2 * i + 1, m, r);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
 
    SegTree st(MAXD);
    FOR (i, MAXD) {
        st.update(i, i + 1, {i});
    }

    ll n, q;
    cin >> n >> q;
    // [y, x, r]
    vector<tuple<ll, ll, ll>> circles(n);
    FOR (i, n) {
        ll x, y, r;
        cin >> x >> y >> r;
        circles[i] = {y, x, r};
    }
    ssort(circles);
    FOR (i, n) {
        ll y, x, r;
        tie(y, x, r) = circles[i];
        // [x - r, x) : query(x-r)
        // [x, x + 1) : query(x-r) U query(x + r)
        // [x + 1, x + r + 1) : query(x + r)
        auto lo = st.query(x - r), hi = st.query(x + r), mid = lo;
        mid.insert(all(hi));
        st.update(x - r, x, lo);
        st.update(x, x + 1, mid);
        st.update(x + 1, x + r + 1, hi);
    }
    st.eval();
    while (q--) {
        ll l, r;
        cin >> l >> r;
        l = all_lo[l];
        r = all_hi[r];
        cout << cnt[r] - cnt[l] + 1 << '\n';
    }

    return 0;
}