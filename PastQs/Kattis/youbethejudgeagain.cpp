#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

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
#define flip(C) reverse(C.begin(), C.end())
#define ssort(C) sort(C.begin(), C.end())
#define rsort(C) sort(C.begin(), C.end(), greater<>())

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
    ll total = ((1 << (2 * n)) - 1) / 3 + 1;
    vector<set<pair<ll, ll>>> pos(total);
    FOR (i, 1 << n) {
        FOR (j, 1 << n) {
            ll idx;
            cin >> idx;
            pos[idx].insert({i, j});
        }
    }
    bool valid = true;
    if (sz(pos[0]) != 1) {
        valid = false;
    } else {
        FOB (i, 1, total) {
            if (sz(pos[i]) != 3) {
                valid = false;
                break;
            }
            vector<pair<ll, ll>> ref;
            FORE (p, pos[i]) {
                ref.pb(p);
            }
            pos[i].insert({ref[0].first, ref[1].second});
            pos[i].insert({ref[0].first, ref[2].second});
            pos[i].insert({ref[1].first, ref[0].second});
            pos[i].insert({ref[1].first, ref[2].second});
            pos[i].insert({ref[2].first, ref[0].second});
            pos[i].insert({ref[2].first, ref[1].second});
            if (sz(pos[i]) != 4) {
                valid = false;
                break;
            }
        }
    }

    if (valid) {
        cout << 1 << '\n';
    } else {
        cout << 0 << '\n';
    }

    return 0;
}