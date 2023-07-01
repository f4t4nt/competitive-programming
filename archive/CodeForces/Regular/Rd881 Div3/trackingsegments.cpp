#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
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

struct BIT {
    vector<ll> tree;
    ll n;

    BIT(ll n) : n(n) {
        tree.resize(n + 1);
    }

    void update(ll idx, ll val) {
        idx++;
        while (idx <= n) {
            tree[idx] += val;
            idx += idx & (-idx);
        }
    }

    ll query(ll idx) {
        idx++;
        ll sum = 0;
        while (idx > 0) {
            sum += tree[idx];
            idx -= idx & (-idx);
        }
        return sum;
    }

    ll query(ll l, ll r) {
        return query(r) - query(l - 1);
    }
};

bool valid(ll mid, ll n, vector<ll> &queries, set<pair<ll, ll>> &segs) {
    BIT bit(n);
    FOR (i, mid) {
        bit.update(queries[i], 1);
    }
    FORE (seg, segs) {
        ll l = seg.first, r = seg.second;
        if (bit.query(l, r) * 2 > r - l + 1) {
            return true;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll t;
    cin >> t;
    while (t--) {
        ll n, m;
        cin >> n >> m;
        set<pair<ll, ll>> segs;
        FOR (i, m) {
            ll l, r;
            cin >> l >> r;
            l--, r--;
            segs.insert({l, r});
        }
        ll q;
        cin >> q;
        vector<ll> queries(q);
        FOR (i, q) {
            cin >> queries[i];
            queries[i]--;
        }
        ll lo = 0, hi = q + 1;
        while (lo < hi) {
            ll mid = (lo + hi) / 2;
            if (valid(mid, n, queries, segs)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        if (lo == q + 1) {
            lo = -1;
        }
        cout << lo << '\n';
    }

    return 0;
}