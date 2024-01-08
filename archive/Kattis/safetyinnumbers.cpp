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

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll T; cin >> T;
    FOR (t, T) {
        ll n; cin >> n;
        vector<ld> js(n);
        FOR (i, n) cin >> js[i];
        ld sum = accumulate(all(js), 0.0);
        vector<ld> rv(n);
        FOR (i, n) {
            ld lo = 0, hi = 1;
            while (hi - lo > 1e-15) {
                ld mid = (lo + hi) / 2,
                    target = js[i] + sum * mid,
                    rem = 0;
                FOR (j, n) {
                    if (i != j && js[j] < target) {
                        rem += target - js[j];
                    }
                }
                if (rem >= (1 - mid) * sum) hi = mid;
                else lo = mid;
            }
            rv[i] = lo * 100;
        }
        cout << "Case #" << t + 1 << ": ";
        FOR (i, n) cout << fixed << setprecision(6) << rv[i] << " \n"[i == n - 1];
    }

    return 0;
}