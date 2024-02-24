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

ld h, r, d_a, d_w;

ld eval(ld y) {
    return (d_w * y * y + d_a * (h * h - y * y)) / (d_w * y + d_a * (h - y));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> h >> r >> d_a >> d_w;
    ld lo = 0, hi = h;

    while (abs(lo - hi) > 1e-9) {
        ld mid1 = (lo * 2 + hi) / 3,
            mid2 = (lo + hi * 2) / 3;
        ld val1 = eval(mid1), val2 = eval(mid2);
        if (val1 > val2) {
            lo = mid1;
        } else {
            hi = mid2;
        }
    }

    cout << fixed << setprecision(10) << lo << '\n';

    return 0;
}