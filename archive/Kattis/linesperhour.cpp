#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef char ch;
typedef string str;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie();
    ll n, s;
    cin >> n >> s;
    s *= 5;

    vector<ll> nums;
    for (ll i= 0; i < n; i++) {
        ll a; cin >> a;
        nums.push_back(a);
    }

    sort(nums.begin(), nums.end());
    ll ct = 0;
    for (int i = 0 ;i < n; i++) {
        ct += nums[i];
        if (ct > s) {
            cout << i << "\n";
            return 0;
        }
    }

    cout << n << "\n";
    return 0;
}