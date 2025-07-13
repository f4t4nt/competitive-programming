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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n, a, b; cin >> n >> a >> b;
        if (a + b > n || ((a == 0) ^ (b == 0))) {
            cout << "NO\n";
            continue;
        }
        vector<ll> A(n), B(n);
        iota(all(A), 1);
        ll m = a + b;
        for (ll i = 0; i < m; i++)
            B[i] = (i + a) % m + 1;
        for (ll i = m; i < n; i++)
            B[i] = i + 1;
        cout << "YES\n";
        for (ll x : A) cout << x << ' ';
        cout << '\n';
        for (ll x : B) cout << x << ' ';
        cout << '\n';
    }

    return 0;
}
