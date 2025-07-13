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

bool is_triangular(ll n) {
    ll x = (sqrt(1 + 8 * n) - 1) / 2;
    return x * (x + 1) / 2 == n;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        if (is_triangular(n)) cout << 1 << '\n';
        else {
            bool ans2 = false;
            for (ll i = 1; i * (i + 1) / 2 <= n; i++) {
                ll t = i * (i + 1) / 2;
                if (is_triangular(n - t)) {
                    ans2 = true;
                    break;
                }
            }
            cout << (ans2 ? 2 : 3) << '\n';
        }
    }

    return 0;
}
