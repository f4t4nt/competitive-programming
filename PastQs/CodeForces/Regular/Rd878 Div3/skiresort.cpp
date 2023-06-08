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
#define FOB(x, b, e) for(auto x = b; x != e; x++)
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
        ll n, k, q;
        cin >> n >> k >> q;
        vector<ll> a(n);
        FOR (i, n) {
            cin >> a[i];
        }
        vector<ll> ref;
        multiset<ll> tmp;
        FOR (i, n) {
            if (a[i] <= q) {
                tmp.insert(a[i]);
            } else {
                ref.pb(sz(tmp));
                tmp.clear();
            }
        }
        ref.pb(sz(tmp));
        ll rv = 0;
        FORE (x, ref) {
            ll y = max(0LL, x - k + 1);
            rv += y * (y + 1) / 2;
        }
        cout << rv << '\n';
    }
    
    return 0;
}