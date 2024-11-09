#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const long long mod = 1e9 + 7;

int main() {
    ll N; cin >> N;
    vector<ll> songs(N);
    for (ll &x : songs) cin >> x;

    ll cnt1 = 0, cur = 0, tot = 0;
    for (ll &x : songs) {
        if (x == 1) {
            cnt1 = (cnt1 + 1) % mod;
            cur = (cur + 1) % mod;
        } else if (x == 2) {
            cur = (cur * 2) % mod;
        } else {
            tot = (tot + cur - cnt1 + mod) % mod;
        }
    }

    cout << tot << endl;
}