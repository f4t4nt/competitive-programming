#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

ll eval(ll F, vector<tuple<ll, ll, ll>> &sinks) {
    ld res = 0;
    for (auto &[t, a, b] : sinks) {
        res += t * a;
        F -= a;
    }
    for (auto &[t, a, b] : sinks) {
        ll d = b - a;
        if (d >= F) {
            res += t * F;
            F = 0;
            break;
        } else {
            res += t * d;
            F -= d;
        }
    }
    return res;
}

int main() {
    ll k, mx = 0, mn = 0; cin >> k;
    vector<tuple<ll, ll, ll>> sinks(k);
    for (ll i = 0; i < k; i++) {
        ll t, a, b;
        cin >> t >> a >> b;
        sinks[i] = {t, a, b};
        mx += b;
        mn += a;
    }
    sort(sinks.begin(), sinks.end());
    auto sinks_inv = sinks;
    reverse(sinks_inv.begin(), sinks_inv.end());
    for (auto &[t, a, b] : sinks_inv) t = -t;
    ll q; cin >> q;
    while (q--) {
        ll T, F; cin >> T >> F;
        if (F < mn || F > mx) {
            cout << "no\n";
            continue;
        }
        ll mn_t = eval(F, sinks),
            mx_t = -eval(F, sinks_inv);
        T *= F;
        cout << (mn_t <= T && T <= mx_t ? "yes" : "no") << '\n';
    }
    
    return 0;
}