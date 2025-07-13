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
        ll n, k; cin >> n >> k;
        vector<ll> a(n);
        for (ll &x: a) cin >> x;
        if (k == 1) { cout << "YES\n"; continue; }

        bool pal = true;
        for (ll i = 0; i < n - i - 1; i++)
            if (a[i] != a[n - i - 1]) { pal = false; break; }
        if (pal) { cout << "YES\n"; continue; }

        vector<ll> freq(n + 1);
        for (ll v : a) freq[v]++;

        ll cnt = 0, tmp = -1;
        for (ll v = 1; v <= n; v++) {
            cnt += freq[v];
            if (cnt >= k) { tmp = v; break; }
        }

        ll rem = cnt - k + 1, l = 0, r = n - 1, del = 0;
        bool ok = true;
        while (l < r) {
            if (a[l] == a[r]) {
                l++; r--;
                continue;
            }
            if (del >= n - k + 1) { ok = false; break; }
            if (a[l] > tmp) {
                l++; del++;
            } elif (a[r] > tmp) {
                r--; del++;
            } elif (a[l] == tmp && rem > 0) {
                l++; del++; rem--;
            } elif (a[r] == tmp && rem > 0) {
                r--; del++; rem--;
            } else {
                ok = false; break;
            }
        }

        cout << (ok ? "YES\n" : "NO\n");
    }

    return 0;
}
