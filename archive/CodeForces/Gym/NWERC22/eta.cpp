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

    str s; cin >> s;
    ll len = 0;
    while (s[len] != '/') len++;
    ll a = stoll(s.substr(0, len)), b = stoll(s.substr(len + 1));
    if (a < b) {
        if (a + 1 == b) {
            cout << b << ' ' << a << '\n';
            FOR (i, a) {
                cout << 1 << ' ' << i + 2 << '\n';
            }
            return 0;
        } else {
            cout << "impossible\n";
            return 0;
        }
    }
    ll mx = a / b + 1;
    vector<ll> lvls(mx + 1, 1);
    ll sum = mx * (mx - 1) / 2, cnt = mx;
    lvls[mx] = 0;
    while (sum * b != a * cnt) {
        ll cur = mx;
        cnt++;
        sum += cur;
        while (cur > 0 && sum * b > a * cnt) {
            sum--;
            cur--;
        }
        assert(cur != 0);
        lvls[cur]++;
    }
    ll par = 1, idx = 2, lvl = 1;
    cout << cnt << ' ' << cnt - 1 << '\n';
    while (idx <= cnt) {
        FOR (i, lvls[lvl]) {
            cout << par << ' ' << idx++ << '\n';
        }
        par = idx - 1;
        lvl++;
    }

    return 0;
}