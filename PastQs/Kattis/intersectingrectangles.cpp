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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    // where a rectangle starts and ends
    vector<pair<ll, ll>> xs(2 * n);
    // where a rectangle starts and ends for a given x
    map<ll, pair<ll, ll>> ys;
    // all coords in [-1e9, 1e9]
    FOR (i, n) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        xs[i] = mp(x1, 2 * i);
        xs[i + n] = mp(x2, 2 * i + 1);
        ys[x1] = mp(y1, y2);
        ys[x2] = mp(y1, y2);
    }

    ssort(xs);

    bool intersect = false;
    set<ll> ys_set;
    FOR (i, 2 * n) {
        ll x, id, y1, y2;
        tie(x, id) = xs[i];
        if (id % 2 == 0) {
            tie(y1, y2) = ys[x];
            auto it = ys_set.upper_bound(y1);
            if (it != ys_set.end() && *it < y2) {
                intersect = true;
                break;
            }
            ys_set.insert(y1);
            ys_set.insert(y2);
        } else {
            tie(y1, y2) = ys[x];
            auto it = ys_set.upper_bound(y1);
            if (it != ys_set.end() && *it < y2) {
                intersect = true;
                break;
            }
            ys_set.erase(y1);
            ys_set.erase(y2);
        }
    }

    cout << (intersect ? 1 : 0) << '\n';

    return 0;
}