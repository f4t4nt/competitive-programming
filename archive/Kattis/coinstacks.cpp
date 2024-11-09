#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    ll n, mx = 0, tot = 0; cin >> n;
    vector<ll> a(n);
    for (ll &x : a) {
        cin >> x;
        mx = max(mx, x);
        tot += x;
    }
    if (tot & 1) cout << "no\n";
    else if (mx * 2 > tot) cout << "no\n";
    else {
        cout << "yes\n";
        while (tot) {
            ll p1 = 0, p2 = 0;
            for (ll i = 0; i < n; i++) {
                if (a[i] > a[p1]) {
                    p1 = i;
                }
            }
            for (ll i = (p1 + 1) % n; i != p1; i = (i + 1) % n) {
                if (a[i]) {
                    p2 = i;
                    break;
                }
            }
            a[p1]--, a[p2]--;
            cout << p1 + 1 << ' ' << p2 + 1 << '\n';
            tot -= 2;
        }
    }
}