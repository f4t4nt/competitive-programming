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

    ll n, m, k;
    cin >> n >> m >> k;
    vector<ll> f(n + m), g(n + m);
    FOR (i, n) cin >> f[i];
    ll sum = 0;
    stack<pair<ll, ll>> stk;

    FOR (i, n + m) {
        stk.push({f[i], i});
        if (i >= m) {
            sum -= g[i - m];
        }
        while (sum < k && sz(stk) > 0 && stk.top().second > i - m) {
            ll del = k - sum;
            auto tmp = stk.top();
            stk.pop();
            if (del > tmp.first) {
                g[tmp.second] += tmp.first;
                sum += tmp.first;
            } else {
                g[tmp.second] += del;
                sum += del;
                stk.push({tmp.first - del, tmp.second});
            }
        }
    }

    ll rv = 0;
    FORE (x, g) rv += x;
    cout << rv << '\n';

    return 0;
}