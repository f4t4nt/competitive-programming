#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    ll n, k; cin >> n >> k;
    map<ll, ll> ref;
    ref[k + 1] = 1;
    while (ref.rbegin()->first < n) {
        auto [x, v] = *ref.rbegin();
        ref[x * k + 1] = v * k + 1;
        if (ref.size() == k) {
            break;
        }
    }
    ll ans = 0;
    if (n > ref.rbegin()->first) {
        ans = n - ref.rbegin()->first;
        n = ref.rbegin()->first;
    }
    for (auto it = ref.rbegin(); it != ref.rend() && n > 0; it++) {
        auto [x, v] = *it;
        ll cnt = n / x;
        n %= x;
        ans += cnt * v;
    }
    cout << ans << '\n';

    return 0;
}