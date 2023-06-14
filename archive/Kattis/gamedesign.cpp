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
#define FORR (x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(ll x = b; x < (ll) e; x++)
#define FORE(x, C) for (auto &x : C)

int main() {
    str s;
    cin >> s;
    if (sz(s) > 2) {
        if ((s.back() == 'R' && s[sz(s) - 2] == 'L' && s[sz(s) - 3] == 'R') ||
            (s.back() == 'L' && s[sz(s) - 2] == 'R' && s[sz(s) - 3] == 'L') ||
            (s.back() == 'U' && s[sz(s) - 2] == 'D' && s[sz(s) - 3] == 'U') ||
            (s.back() == 'D' && s[sz(s) - 2] == 'U' && s[sz(s) - 3] == 'D'))
        {
            cout << "impossible\n";
            return 0;
        }
    }

    ll len = 3;
    pair<ll, ll> cur = {0, 0};
    vector<pair<ll, ll>> rv = {{0, 0}};
    FOR (i, sz(s)) {
        if (i > 0) {
            if ((s[i] == 'R' && s[i - 1] == 'L') ||
                (s[i] == 'L' && s[i - 1] == 'R'))
            {
                cur.first *= -1;
                continue;
            } elif ((s[i] == 'U' && s[i - 1] == 'D') ||
                (s[i] == 'D' && s[i - 1] == 'U'))
            {
                cur.second *= -1;
                continue;
            }
        }
        if (s[i] == 'L' || s[i] == 'R') {
            rv.pb({len, cur.second});
            rv.pb({-len, cur.second});
            if (s[i] == 'R') {
                cur.first = len - 1;
            } else {
                cur.first = -len + 1;
            }
        } elif (s[i] == 'U' || s[i] == 'D') {
            rv.pb({cur.first, len});
            rv.pb({cur.first, -len});
            if (s[i] == 'U') {
                cur.second = len - 1;
            } else {
                cur.second = -len + 1;
            }
        }
        len++;
    }

    FORE (x, rv) {
        x.first -= cur.first;
        x.second -= cur.second;
    }

    cout << rv[0].first << ' ' << rv[0].second << '\n' << sz(rv) - 1 << '\n';
    FOB (i, 1, sz(rv)) {
        cout << rv[i].first << ' ' << rv[i].second << '\n';
    }

    return 0;
}