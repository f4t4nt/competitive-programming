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

const ll MOD = 1e9 + 7;

map<ll, ll> factorize(ll n) {
    map<ll, ll> f;
    while (n % 2 == 0)
        f[2]++, n /= 2;
    for (ll i = 3; i * i <= n; i += 2) {
        while (n % i == 0)
            f[i]++, n /= i;
    }
    if (n > 2) f[n]++;
    return f;
}

void upd(map<ll, ll> &lcm_f, ll cyc) {
    map<ll, ll> f = factorize(cyc);
    for (auto &[p, e] : f)
        lcm_f[p] = max(lcm_f[p], e);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n; cin >> n;
    vector<ll> p(n);
    for (ll &x : p) cin >> x, x--;
    vector<bool> vis(n);
    map<ll, ll> lcm_f;
    for (ll i = 0; i < n; i++) {
        if (vis[i]) continue;
        ll j = i, c = 0;
        while (!vis[j]) {
            vis[j] = true;
            j = p[j];
            c++;
        }
        upd(lcm_f, c);
    }
    ll ans = 1;
    for (auto &[p, e] : lcm_f) {
        ll pp = 1, base = p % MOD;
        for (ll i = 0; i < e; i++)
            pp = (pp * base) % MOD;
        ans = (ans * pp) % MOD;
    }
    cout << ans << '\n';

    return 0;
}
