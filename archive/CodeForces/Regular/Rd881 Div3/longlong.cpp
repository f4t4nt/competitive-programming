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
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        vector<ll> a(n);
        FOR (i, n) {
            cin >> a[i];
        }
        ll rv0 = 0, rv1 = 0, cnt = 0;
        FOR (i, n) {
            if (a[i] < 0) {
                cnt = 1;
            } elif (a[i] == 0 && cnt == 1) {
                cnt = 1;
            } else {
                rv1 += cnt;
                cnt = 0;
            }
            rv0 += abs(a[i]);
        }
        rv1 += cnt;
        cout << rv0 << ' ' << rv1 << '\n';
    }

    return 0;
}