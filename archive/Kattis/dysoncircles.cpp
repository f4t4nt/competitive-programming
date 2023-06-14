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
    if (n == 1) {
        cout << 4 << '\n';
        return 0;
    }

    vector<pair<ll, ll>> stars(n);
    FOR (i, n) {
        cin >> stars[i].first >> stars[i].second;
    }
    vector<ll> ref(4, -1e18);
    set<ll> diag0, diag1;
    
    FOR (i, n) {
        ref[0] = max(stars[i].first + stars[i].second, ref[0]);
        ref[1] = max(stars[i].first - stars[i].second, ref[1]);
        ref[2] = max(-stars[i].first - stars[i].second, ref[2]);
        ref[3] = max(-stars[i].first + stars[i].second, ref[3]);
        diag0.insert(stars[i].first + stars[i].second);
        diag1.insert(stars[i].first - stars[i].second);
    }

    ll rv = ref[0] + ref[1] + ref[2] + ref[3] + 4;
    if (sz(diag0) == 1 || sz(diag1) == 1) {
        rv++;
    }
    cout << rv << '\n';

    return 0;
}