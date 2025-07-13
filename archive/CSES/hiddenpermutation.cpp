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

    ll n; cin >> n;
    vector<ll> ord = {0}, ans(n);
    for (ll i = 1; i < n; i++) {
        ll lo = 0, hi = sz(ord);
        while (lo < hi) {
            ll mid = (lo + hi) / 2;
            cout << "? " << i + 1 << ' ' << ord[mid] + 1 << endl;
            str s; cin >> s;
            if (s == "YES") hi = mid;
            else lo = mid + 1;
        }
        ord.insert(ord.begin() + lo, i);
    }
    for (ll i = 0; i < n; i++) ans[ord[i]] = i;
    cout << "! ";
    for (ll x : ans) cout << x + 1 << ' ';
    cout << endl;

    return 0;
}
