#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef char ch;
typedef string str;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define x first
#define y second
#define ssort(C) sort(all(C))

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll c, d;
    cin >> c >> d;

    vector<ll> fizz, buzz;

    for (ll i = c; i <= d; i++) {
        string s;
        cin >> s;
        if (s.find("Fizz") != s.npos) {
            fizz.pb(i);
        }
        if (s.find("Buzz") != s.npos) {
            buzz.pb(i);
        }
    }
    
    if (sz(fizz) == 0) {
        cout << d + 1 << " ";
    }
    else if (sz(fizz) == 1) {
        cout << fizz[0] << " ";
    }
    else {
        cout << fizz[1] - fizz[0] << " ";
    }

    if (sz(buzz) == 0) {
        cout << d + 2 << " ";
    }
    else if (sz(buzz) == 1) {
        cout << buzz[0] << " ";
    }
    else {
        cout << buzz[1] - buzz[0] << " ";
    }


    return 0;
}