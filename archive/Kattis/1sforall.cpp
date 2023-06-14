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
    vector<ll> dist(n + 1, 1e18);
    dist[1] = 1;
    FOB (i, 2, n + 1) {
        FOB (j, 1, i / 2 + 1) {
            dist[i] = min(dist[i], dist[j] + dist[i - j]);
        }
        for (ll j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                dist[i] = min(dist[i], dist[j] + dist[i / j]);
            }
        }
        str i_s = to_string(i);
        FOB (j, 1, sz(i_s)) {
            str a_s = i_s.substr(0, j), b_s = i_s.substr(j, sz(i_s) - j);
            if (b_s[0] == '0') {
                continue;
            }
            ll a = stoll(a_s), b = stoll(b_s);
            dist[i] = min(dist[i], dist[a] + dist[b]);
        }
    }
    cout << dist[n] << '\n';

    return 0;
}