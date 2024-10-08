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
    if ((n * (n + 1) / 2) % 2 == 1) {
        cout << "NO\n";
        return 0;
    }
    vector<bool> ref(n + 1);
    set<ll> s0, s1;
    ll x = n, tmp = n * (n + 1) / 4;
    while (tmp) {
        ref[x] = true;
        tmp -= x;
        s0.insert(x);
        x = min(x - 1, tmp);
    }
    FOB (i, 1, n + 1) {
        if (!ref[i]) {
            s1.insert(i);
        }
    }
    cout << "YES\n";
    cout << sz(s0) << '\n';
    FORE (i, s0) {
        cout << i << ' ';
    }
    cout << '\n';
    cout << sz(s1) << '\n';
    FORE (i, s1) {
        cout << i << ' ';
    }
    cout << '\n';

    return 0;
}