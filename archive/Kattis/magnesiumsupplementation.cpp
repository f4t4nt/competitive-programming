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

    vector<ll> works;
    ll n, k, p;
    cin >> n >> k >> p;

    ll lo = (n + p - 1) / p;
    ll hi = k;
    for (ll i = 1; i * i <= n; i++) {
        if (n % i != 0) continue;
        if (i >= lo && i <= hi) works.push_back(i);
        if (i * i != n && n / i >= lo && n / i <= hi) works.push_back(n / i);
    }

    sort(works.begin(), works.end());
    cout << works.size() << '\n';
    for (auto x : works) {
        cout << x << "\n";
    }
}