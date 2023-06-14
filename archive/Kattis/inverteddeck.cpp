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
 
ll INF = 1LL * 2000000000 * 2000000000;
 
int32_t main() {
    ll n;
    cin >> n;
    
    vector<ll> a(n+2);
    for (ll i = 0 ; i < n ; i++) cin >> a[i+1];
    a[0] = -INF;
    a[n+1] = INF;
    
    vector<pair<ll, ll>> c;
    
    for (ll i = 0 ; i < n+2 ; i++) {
        c.push_back({a[i], i});
    }
    
    sort(c.begin(), c.end());
    
    ll start = -1;
    ll end = -1;
    
    /*
     8
     1 1 2 2 3 5 4 6
     */
    
    ll ev = -1;
    for (ll i = 1 ; i < n+2 ; i++) {
        if (c[i].second != c[i - 1].second + 1) {
            ev = c[i].first;
            start = c[i - 1].second + 1;
            break;
        }
    }
    
    end = -1;
    for (ll i = 0 ; i < n+2 ; i++) {
        if (a[i] == ev) {
            end = i;
        }
    }
        
    if (start == -1) {
        cout << "1 1" << endl;
        return 0;
    }
    
    vector<ll> b(n+2);
    for (ll i = 0 ; i < n+2 ; i++) {
        if (i < start || i > end) {
            b[i] = a[i];
        }
        else {
            b[i] = a[start + (end - start) - (i - start)];
        }
    }
    
    bool valid = true;
    for (ll i = 1 ; i < n+2 ; i++) {
        valid &= (b[i] >= b[i-1]);
    }
    
    if (!valid) {
        cout << "impossible" << endl;
    }
    else {
        cout << start << " " << end << endl;
    }
}