#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef complex<long double> cd;
typedef long double ld;
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

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
#define f first
#define s second

// #ifdef LOCAL
// #include "tester.cpp"
// #define main test_main
// extern istringstream fin;
// extern ostringstream fout;
// string test_file_name = "tests";
// #define cin fin
// #define cout fout
// #endif

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n, k; cin >> n >> k;
        if (n == 2 * k) {
            cout << "! " << k << " " << k << endl;
            continue;
        }
        vector<ll> a(k), b(k);
        for (ll i = 0; i < k; i++) {
            cout << "? " << i + 1 << endl;
            cin >> a[i];
        }
        for (ll i = n - k; i < n; i++) {
            cout << "? " << i + 1 << endl;
            cin >> b[i % k];
        }
        if (a == b) {
            cout << "! " << -1 << endl;
            continue;
        }
        bool ok = true;
        ll lo = k, hi = n - k;
        while (lo < hi) {
            ll mid = (lo + hi) / 2, cnt = 0;
            while (mid > lo && a[mid % k] == b[mid % k]) mid--;
            while (mid < hi - 1 && a[mid % k] == b[mid % k]) mid++;
            if (a[mid % k] == b[mid % k]) {
                ok = false;
                break;
            }
            cout << "? " << mid + 1 << endl;
            ll x; cin >> x;
            if (b[mid % k] == x) hi = mid;
            else lo = mid + 1;
        }
        if (!ok) {
            cout << "! " << -1 << endl;
        } else {
            cout << "! " << lo << " " << n - lo << endl;
        }
    }

    return 0;
}