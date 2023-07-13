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

// #ifdef LOCAL
// #include "tester.cpp"
// #define main test_main
// extern istringstream fin;
// extern ostringstream fout;
// string test_file_name = "tests";
// #define cin fin
// #define cout fout
// #endif

void solve(ll cur_n, vector<ll> &a, vector<vector<ll>> &cnt) {
    while (true) {
        cnt.pb(vector<ll>(9));
        FOR (i, cur_n) {
            cin >> a[i];
            cnt.back()[a[i] - 1]++;
        }
        if (sz(cnt) < 2 || cnt.back() == cnt[sz(cnt) - 2]) {
            cout << "- 0" << endl;
        } else {
            vector<ll> rem;
            FOR (i, cur_n) {
                if (cnt.back()[a[i] - 1] <= cnt[sz(cnt) - 2][a[i] - 1]) {
                    rem.pb(i);
                }
                if (cnt.back()[a[i] - 1] == 1 && cnt[sz(cnt) - 2][a[i] - 1] == 0) {
                    cout << "! " << i + 1 << endl;
                    return;
                }
            }
            cur_n -= sz(rem);
            cout << "- " << sz(rem);
            FORE (i, rem) {
                cnt.back()[a[i] - 1]--;
                cout << " " << i + 1;
            }
            cout << endl;
        }
    }
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        ll cur_n = n;
        vector<ll> a(n);
        vector<vector<ll>> cnt;
        solve(cur_n, a, cnt);
    }

    return 0;
}