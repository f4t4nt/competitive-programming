#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ch = char;
using str = string;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for(ll x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FORE(x, C) for(auto &x : C)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

bool valid(ll mid, ll &s, ll &n, multiset<ll> &a, multiset<ll> b) {
    ll cnt = 0;
    FORE (tx, a) {
        ll x = -tx, target = min(s - x, x + mid);
        auto it = b.upper_bound(target);
        if (it != b.begin()) {
            it--;
            if (abs(*it - x) <= mid) {
                cnt++;
                b.erase(it);
            }
        }
    }
    return cnt >= n;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, p, q, s;
    cin >> n >> p >> q >> s;
    multiset<ll> a, b;
    FOR (i, p) {
        ll x;
        cin >> x;
        a.insert(-x);
    }
    FOR (i, q) {
        ll x;
        cin >> x;
        b.insert(x);
    }
    ll lo = 0, hi = 1e18;
    if (!valid(hi, s, n, a, b)) {
        cout << -1 << '\n';
        return 0;
    }
    while (lo < hi) {
        ll mid = (lo + hi) / 2;
        if (valid(mid, s, n, a, b)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    cout << lo << '\n';

    return 0;
}