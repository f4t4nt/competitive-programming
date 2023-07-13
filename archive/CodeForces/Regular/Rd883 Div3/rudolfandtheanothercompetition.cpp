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
    cin.tie(0);
    cout.tie(0);

    ll t;
    cin >> t;
    while (t--) {
        ll n, m, h, rv = 1, rcnt, rsum;
        cin >> n >> m >> h;
        vector<pair<ll, ll>> ref;
        vector<vector<ll>> times(n, vector<ll>(m));
        FOR (i, n) {
            FOR (j, m) {
                cin >> times[i][j];
            }
            ssort(times[i]);
            vector<ll> tmp;
            ll time = 0, cnt = 0, sum = 0;
            while (cnt < m and time + times[i][cnt] <= h) {
                tmp.pb(times[i][cnt]);
                time += times[i][cnt];
                cnt++;
            }
            time = 0;
            FOR (j, cnt) {
                time += tmp[j];
                sum += time;
            }
            if (i == 0) {
                rcnt = cnt;
                rsum = sum;
            } elif (cnt > rcnt || (cnt == rcnt && sum < rsum)) {
                rv++;
            }
        }
        cout << rv << '\n';
    }

    return 0;
}