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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll t;
    cin >> t;
    while (t--) {
        ll q;
        cin >> q;
        vector<ll> par = {0};
        vector<vector<ll>> cur = {{0, 1}}, maxx = {{0, 1}};
        while (q--) {
            ch c;
            cin >> c;
            if (c == '+') {
                ll p, x;
                cin >> p >> x;
                p--;
                ll q = sz(par);
                par.pb(p);
                cur.pb(cur[p]);
                cur[q][0] = min(cur[q][0] + x, 0LL);
                cur[q][1] = max(cur[q][1] + x, 0LL);
                maxx.pb(maxx[p]);
                maxx[q][0] = min(maxx[q][0], cur[q][0]);
                maxx[q][1] = max(maxx[q][1], cur[q][1]);
            } else {
                ll u, v, k;
                cin >> u >> v >> k;
                u--, v--;
                assert(u == 0);
                if (maxx[v][0] <= k && k <= maxx[v][1]) {
                    cout << "YES\n";
                } else {
                    cout << "NO\n";
                }
            }
        }
    }

    return 0;
}