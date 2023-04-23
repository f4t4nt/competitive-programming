#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using cd = complex<double>;
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

    ll t;
    cin >> t;
    while (t--) {
        ll n, k, total = 0;
        cin >> n >> k;
        vector<ll> l(n), r(n), len(n);
        FOR (i, n) {
            cin >> l[i];
        }
        FOR (i, n) {
            cin >> r[i];
            len[i] = r[i] - l[i] + 1;
            total += len[i];
        }
        if (total < k) {
            cout << -1 << '\n';
            continue;
        }
        ll sum = 0, cnt1s = 0, no1s = 0, rv = 1e18;
        FOR (i, n) {
            if (sum >= k && cnt1s == 0) {
                break;
            }
            sum += len[i];
            if (len[i] == 1) {
                cnt1s++;
            } else {
                no1s++;
            }
            while (cnt1s > 0 && sum > k) {
                sum--;
                cnt1s--;
            }
            if (sum >= k) {
                ll prev = sum - len[i];
                ll idx = min(r[i], l[i] + k - prev - 1);
                rv = min(rv, idx + (no1s + cnt1s) * 2);
            }
        }
        cout << rv << '\n';
    }

    return 0;
}