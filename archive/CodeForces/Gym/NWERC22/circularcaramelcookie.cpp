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

    ll t = 1;// cin >> t;
    while (t--) {
        ll n; cin >> n;
        ll lo = 2, hi = 1e12;
        while (lo < hi) {
            ll mid = (lo + hi) / 2;
            ll r = sqrt(mid) + 5;
            while (r * r > mid) r--;
            ll cnt = 0;
            while (r) {
                cnt += (ll) floor(sqrt(mid - r * r + 0.5));
                r--;
            }
            cnt *= 4;
            if (cnt > n) hi = mid;
            else lo = mid + 1;
        }
        cout << fixed << setprecision(10) << sqrt(lo) << endl;
    }

    return 0;
}