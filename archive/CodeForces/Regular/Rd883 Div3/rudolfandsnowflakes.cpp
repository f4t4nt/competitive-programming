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

    set<ll> s;
    FOB (i, 2, 1e6 + 1) {
        ll p = 0, sum = 0, cur = 1;
        while (sum <= 1e18) {
            sum += cur;
            if (p >= 2) s.insert(sum);
            if (cur > 1e18 / i) break;
            cur *= i;
            p++;
        }
    }

    ll t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        if (s.count(n)) cout << "YES\n";
        else {
            ld tmp = (sqrt(4 * n - 3) - 1) / 2;
            tmp = round(tmp);
            tmp = max(tmp, (ld) 3);
            vector<ll> tests = {(ll) tmp - 1, (ll) tmp, (ll) tmp + 1};
            bool ok = false;
            FORE (i, tests) {
                if (i * i + i + 1 == n) {
                    ok = true;
                    break;
                }
            }
            if (ok) cout << "YES\n";
            else cout << "NO\n";
        }
    }

    return 0;
}