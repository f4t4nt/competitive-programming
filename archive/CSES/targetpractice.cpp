#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef complex<long double> cd;
typedef long double ld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

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

bool collinear(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3){
    return (y1 - y2) * (x1 - x3) == (y1 - y3) * (x1 - x2);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    vector<ll> xs(n), ys(n);
    FOR(i, n) cin >> xs[i] >> ys[i];
    if (n <= 2) {
        cout << "success\n";
        return 0;
    }
    FOR (_, 1e3) {
        ll a = rng() % n, b = rng() % n;
        while (a == b) b = rng() % n;
        vector<ll> others;
        FOR(i, n) {
            if (!collinear(xs[a], ys[a], xs[b], ys[b], xs[i], ys[i])) {
                others.pb(i);
            }
        }
        bool ok = true;
        FOB (i, 2, sz(others)) {
            if (!collinear(xs[others[0]], ys[others[0]], xs[others[1]], ys[others[1]], xs[others[i]], ys[others[i]])) {
                ok = false;
                break;
            }
        }
        if (ok) {
            cout << "success\n";
            return 0;
        }
    }
    cout << "failure\n";

    return 0;
}