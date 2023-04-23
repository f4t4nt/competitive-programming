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
#define mp make_pair
#define mt make_tuple
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for(ll x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FOI(x, e, i) for(ll x = 0; x < (ll) e; x += (ll) i)
#define FOBI(x, b, e, i) for(ll x = (ll) b; x < (ll) e; x += (ll) i)
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

    BIT(ll n) {
        this->n = n;
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

ld get_angle(ld x0, ld x, ld y) {
    return atan2(y, x - x0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);   
    cout.tie(nullptr);

    ll n;
    ld x;
    cin >> n >> x;
    vector<tuple<ld, ld, ll>> v(n);
    FOR (i, n) {
        ld x_, y;
        ll p, idx_a;
        cin >> x_ >> y >> p;
        v[i] = {x_, y, p};
    }
    // angle, idx, prefix idx
    vector<pair<ld, ll>> angles_0(n), angles_x(n);
    FOR (i, n) {
        angles_0[i] = {get_angle(0, get<0>(v[i]), get<1>(v[i])), i};
        angles_x[i] = {get_angle(x, get<0>(v[i]), get<1>(v[i])), i};
    }
    rsort(angles_0);
    rsort(angles_x);
    vector<ll> ref(n);
    FOR (i, n) {
        ref[angles_0[i].second] = i;
    }
    vector<pair<ll, ll>> sorted(n);
    FOR (i, n) {
        sorted[i] = {get<2>(v[angles_x[i].second]),
            ref[angles_x[i].second]};
    }

    BIT bit(n);
    vector<ll> rv(n);
    FOR (i, n) {
        rv[angles_x[i].second] = bit.query(sorted[i].second, n - 1);
        bit.update(sorted[i].second, sorted[i].first);
    }
    FOR (i, n) {
        cout << rv[i] << '\n';
    }

    return 0;
}