#include <bits/stdc++.h>
using namespace std;

typedef __int128 i128;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef double ld;
typedef complex<ld> cd;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
// #define f first
// #define s second

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

    ll n; cin >> n;
    ll mx_add = -1e18, mn_add = 1e18,
        mx_sub = -1e18, mn_sub = 1e18;
    while (n--) {
        ll x, y; cin >> x >> y;
        mx_add = max(mx_add, x + y);
        mn_add = min(mn_add, x + y);
        mx_sub = max(mx_sub, x - y);
        mn_sub = min(mn_sub, x - y);
        cout << max(mx_add - mn_add, mx_sub - mn_sub) << '\n';
    }

    return 0;
}
