#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef char ch;
typedef string str;

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie();

    ll n, a, b, mn = 1e9, mx = 0; cin >> n >> a >> b;
    vector<ll> log(n - 1);
    FOR (i, n - 1) {
        cin >> log[i];
        mn = min(mn, log[i]);
        mx = max(mx, log[i]);
    }

    if (mn != a && mx != b) {
        cout << -1 << '\n';
    } else if (mn != a) {
        cout << a << '\n';
    } else if (mx != b) {
        cout << b << '\n';
    } else {
        for (ll i = a; i <= b; i++) {
            cout << i << '\n';
        }
    }
}