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

pair<ld, ld> quadratic(ld a, ld b, ld c) {
    ld d = b * b - 4 * a * c;
    assert(d >= 0);
    ld x1 = (-b + sqrt(d)) / (2 * a),
        x2 = (-b - sqrt(d)) / (2 * a);
    return {x1, x2};
}

ld get_t(ld xi, ld x, ld xvi, ld yi, ld y, ld yvi, ld v) {
    ld a = xvi * xvi + yvi * yvi - v * v,
        b = 2 * (xvi * (xi - x) + yvi * (yi - y)),
        c = (xi - x) * (xi - x) + (yi - y) * (yi - y);
    auto [t1, t2] = quadratic(a, b, c);
    return max(t1, t2);
}

vector<ld> time(ll &n, vector<ll> &ord, ld &v0, vector<ld> xs, vector<ld> ys, vector<ld> &xvs, vector<ld> &yvs, vector<ld> &vs) {
    ld t = 0, x = 0, y = 0;
    vector<ld> times(sz(ord));
    FORE (i, ord) {
        ld dt = get_t(xs[i], x, xvs[i], ys[i], y, yvs[i], v0);
        assert(dt >= 0);
        FOR (i, n) {
            xs[i] += xvs[i] * dt;
            ys[i] += yvs[i] * dt;
        }
        x = xs[i];
        y = ys[i];
        t += dt;
        times[i] = t + sqrt(x * x + y * y) / vs[i];
    }
    times.pb(t + sqrt(x * x + y * y) / v0);
    return times;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while (true) {
        ll n;
        cin >> n;
        if (n == 0) break;
        vector<ll> ord(n), best_ord;
        iota(all(ord), 0);
        ld v0, rv = 1e18;
        vector<ld> xs(n), ys(n), xvs(n), yvs(n), vs(n), times, best_times;
        cin >> v0;
        FOR (i, n) {
            ld ang;
            cin >> xs[i] >> ys[i] >> vs[i] >> ang;
            xvs[i] = vs[i] * cos(ang);
            yvs[i] = vs[i] * sin(ang);
        }
        do {
            times = time(n, ord, v0, xs, ys, xvs, yvs, vs);
            if (*max_element(all(times)) < rv) {
                rv = *max_element(all(times));
                best_ord = ord;
                best_times = times;
            }
        } while (next_permutation(all(ord)));
        cout << (ll) (rv + 0.5) << '\n';
    }

    return 0;
}