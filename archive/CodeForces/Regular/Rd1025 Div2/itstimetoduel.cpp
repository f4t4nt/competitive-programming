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
        ll n, cnt0 = 0; cin >> n;
        vector<ll> a(n);
        for (ll &x : a) {
            cin >> x;
            if (x == 0) cnt0++;
        }
        if (cnt0 == 0) {
            cout << "YES\n";
            continue;
        }
        bool ok = true;
        for (ll i = 1; i < n; i++) {
            if (a[i] == 0 && a[i - 1] == 0) {
                ok = false;
                break;
            }
        }
        cout << (ok ? "NO\n" : "YES\n");
    }

    return 0;
}
