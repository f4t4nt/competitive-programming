#include <bits/stdc++.h>

using namespace std;

using ll = long long;
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
        ll n;
        cin >> n;
        vector<ll> p(n), pos(n);
        FOR (i, n) {
            cin >> p[i];
            p[i]--;
            pos[p[i]] = i;
        }
        // median of pos[0], pos[1], and pos[n - 1]
        ll a = min(pos[0], min(pos[1], pos[n - 1]));
        ll b = max(pos[0], max(pos[1], pos[n - 1]));
        ll c = pos[0] + pos[1] + pos[n - 1] - a - b;
        cout << pos[n - 1] + 1 << ' ' << c + 1 << '\n';
    }

    return 0;
}