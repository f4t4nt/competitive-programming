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

    ll n, k; cin >> n >> k;
    vector<ll> a(n), ans;
    ans.reserve(n - k + 1);
    for (ll &x : a) cin >> x;
    map<ll, ll> cnt;
    for (ll i = 0; i < k; i++)
        cnt[a[i]]++;
    ans.pb(sz(cnt));
    for (ll i = k; i < n; i++) {
        cnt[a[i]]++;
        if (--cnt[a[i - k]] == 0)
            cnt.erase(a[i - k]);
        ans.pb(sz(cnt));
    }
    for (ll x : ans) cout << x << ' ';
    cout << '\n';

    return 0;
}
