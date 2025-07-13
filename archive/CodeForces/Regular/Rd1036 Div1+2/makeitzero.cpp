#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef long double ld;
typedef complex<ld> cd;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

template<typename T>
using indexed_set = tree<
    T,
    null_type,
    less<T>,
    rb_tree_tag,
    tree_order_statistics_node_update>;
// s.order_of_key(x) -> number of elements < x
// s.find_by_order(x) -> iterator to the x-th element (0-indexed)

#pragma GCC target("popcnt,lzcnt")
// __builtin_popcount(x) -> number of set bits
// __builtin_clz(x) -> number of leading zeros
// for ll, use __builtin_popcountll, __builtin_clzll

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
#define x first
#define y second

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        vector<ll> a(n);
        ll sum = 0, mx = 0;
        for (ll &x : a) { cin >> x; sum += x; mx = max(mx, x); }

        if (
            (sum & 1) ||
            (n == 2 && a[0] != a[1]) ||
            (mx > sum / 2)
        ) {
            cout << -1 << '\n';
            continue;
        }

        ll half = sum / 2, pref = 0;
        bool ok = false;
        for (ll i = 0; i < n - 1; i++) {
            pref += a[i];
            if (pref == half) {
                cout << 1 << '\n';
                for (ll x : a) cout << x << ' ';
                cout << '\n';
                ok = true;
                break;
            }
        }
        if (ok) continue;

        pref = 0;
        ll j = -1;
        for (ll i = 0; i < n; ++i) {
            if (pref < half && half < pref + a[i]) { j = i; break; }
            pref += a[i];
        }
        ll i = j - 1, tmp = pref, v = a[j], y = tmp + v - half;

        vector<ll> b1(n, 0);
        ll need = y;
        for (ll k = i; k >= 0 && need; k--) {
            ll take = min(need, a[k]);
            b1[k] = take, need -= take;
        }
        b1[j] = y;

        vector<ll> b2(n);
        for (ll k = 0; k < n; k++) b2[k] = a[k] - b1[k];

        cout << 2 << '\n';
        for (ll x : b1) cout << x << ' ';
        cout << '\n';
        for (ll x : b2) cout << x << ' ';
        cout << '\n';
    }

    return 0;
}
