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
        ll n, x; cin >> n >> x;
        ll b = __builtin_popcountll(x);
        if (n == 1) cout << (x == 0 ? -1 : x) << '\n';
        elif (n <= b) cout << x << '\n';
        elif (n & 1 && x == 0) cout << n + 3 << '\n';
        elif (n & 1 && x == 1) cout << n << '\n';
        elif (n & 1) cout << (n - b + 1) / 2 * 2 + x << '\n';
        elif (x == 0) cout << n << '\n';
        elif (x == 1) cout << n + 3 << '\n';
        else cout << (n - b + 1) / 2 * 2 + x << '\n';
    }

    return 0;
}