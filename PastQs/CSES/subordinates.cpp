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
    vector<ll> bosses(n);
    vector<vector<ll>> direct_subordinates(n);
    FOB (i, 1, n) {
        cin >> bosses[i];
        bosses[i]--;
        direct_subordinates[bosses[i]].pb(i);
    }

    ll max_depth = 0;
    vector<ll> depth(n);
    queue<ll> q;
    q.push(0);
    while (!q.empty()) {
        ll boss = q.front();
        q.pop();
        FORE (subordinate, direct_subordinates[boss]) {
            depth[subordinate] = depth[boss] + 1;
            max_depth = max(max_depth, depth[subordinate]);
            q.push(subordinate);
        }
    }

    vector<vector<ll>> depths(max_depth + 1);
    FOR (i, n) {
        depths[depth[i]].pb(i);
    }

    vector<ll> subordinates(n);
    FORR (i, max_depth + 1) {
        FORE (subordinate, depths[i]) {
            subordinates[subordinate]++;
            if (subordinate != 0) {
                subordinates[bosses[subordinate]] += subordinates[subordinate];
            }
        }
    }

    FORE (subordinate, subordinates) {
        cout << subordinate - 1 << ' ';
    }

    return 0;
}