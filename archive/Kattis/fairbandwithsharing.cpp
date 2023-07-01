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

constexpr ld INF = 1e9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    ld t, total_d = 0, total_cur = 0, total_rem;
    cin >> n >> t;
    total_rem = t;
    vector<ld> a(n), b(n), d(n), rv(n);
    vector<pair<ld, ll>> ord;
    FOR (i, n) {
        cin >> a[i] >> b[i] >> d[i];
        rv[i] = a[i];
        total_rem -= a[i];
        ord.pb({a[i] / d[i], -(i + 1)});
        ord.pb({b[i] / d[i], (i + 1)});
    }
    ord.pb({INF, 0});
    ssort(ord);
    set<ll> active;
    FOR (idx, 2 * n) {
        ld c1 = ord[idx + 1].first;
        ll i = abs(ord[idx].second) - 1;
        if (ord[idx].second < 0) {
            ll sz = sz(active);
            active.insert(i);
            assert(sz < sz(active));
            total_d += d[i];
            total_cur += a[i];
        } else {
            ll sz = sz(active);
            active.erase(i);
            assert(sz > sz(active));
            rv[i] = b[i];
            total_d -= d[i];
            total_cur -= a[i];
            total_rem -= b[i] - a[i];
        }
        ld amt = total_cur + total_rem;
        if (c1 >= INF || amt <= c1 * total_d) {
            FORE (j, active) {
                rv[j] = amt * d[j] / total_d;
            }
            break;
        }
    }
    FORE (x, rv) {
        cout << fixed << setprecision(10) << x << '\n';
    }

    return 0;
}