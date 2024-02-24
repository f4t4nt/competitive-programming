#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef char ch;
typedef string str;
typedef pair<ll, ll> pll;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)

#define f first
#define s second

ll shoelace(vector<pll> v) {
    ll rv = 0;
    FOR (i, sz(v)) {
        rv += (v[i].f * v[(i + 1) % sz(v)].s) -
            (v[i].s * v[(i + 1) % sz(v)].f);
    }
    return rv;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, m;
    cin >> n >> m;

    vector<tuple<ld, ld, ld>> in(n), out(m);
    FOR (i, n) cin >> get<1>(in[i]);
    FOR (i, n) cin >> get<2>(in[i]);
    FOR (i, m) cin >> get<1>(out[i]);
    FOR (i, m) cin >> get<2>(out[i]);
    FOR (i, n) get<0>(in[i]) = get<2>(in[i]) / get<1>(in[i]);
    FOR (i, m) get<0>(out[i]) = get<2>(out[i]) / get<1>(out[i]);
    sort(all(in));
    sort(all(out));

    vector<pll> ins = {{0, 0}}, outs = ins;
    FOR (i, n) {
        ins.pb({ins.back().f + get<1>(in[i]), ins.back().s + get<2>(in[i])});
    }
    FOR (i, m) {
        outs.pb({outs.back().f + get<1>(out[i]), outs.back().s + get<2>(out[i])});
    }

    ll lo = 0;
    for (auto [cx, cy] : outs) {
        while (lo < n - 1 && ins[lo + 1].f < cx) lo++;
        auto [px, py] = ins[lo];
        auto [nx, ny] = ins[lo + 1];
        ll area = shoelace({{px, py}, {nx, ny}, {cx, cy}});
        if (area < 0) {
            cout << "No\n";
            return 0;
        }
    }
    cout << "Yes\n";

    return 0;
}