#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef char ch;
typedef string str;
typedef pair<ll, ll> pll;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define ssort(C) sort(all(C))

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)

ll prv = -1, cur = 0, n;

bool qry(ll l, ll r) {
    if (r >= n) return false;
    cout << l + 1 << ' ' << r + 1 << endl;
    prv = cur;
    cin >> cur;
    return true;
}

bool cover_i_to_n(ll a) { // covers [a, n) with [0, a) uncovered
    for (ll i = a; i < n; i++) {
        qry(i, i);
        if (cur == n) return true;
        if (cur > prv) qry(i, i);
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    vector<ll> offset = {};
    FOR (i, 11) {
        auto tmp = offset;
        offset.pb(i);
        offset.insert(offset.end(), all(tmp));
    }

    cin >> n >> cur;
    if (n == cur) return 0;
    if (cover_i_to_n(0)) return 0;
    FOR (i, n) {
        ll idx = 0;
        while (qry(i, i + offset[idx++])) {
            if (cur == n) return 0;
            if (cur > i) {
                if (cover_i_to_n(i + 1)) return 0;
                if (cur == i + 1) break;
            }
        }
    }

    return 0;
}