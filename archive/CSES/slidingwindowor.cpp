#include <bits/stdc++.h>
using namespace std;

typedef __int128 i128;
typedef unsigned int ll;
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

    ll n, k, x, a, b, c; cin >> n >> k >> x >> a >> b >> c;
    vector<ll> v(n), cnt(30);
    v[0] = x;
    for (ll i = 1; i < n; i++)
        v[i] = ((ull) a * v[i - 1] + b) % c;
    ll ans = 0, cur_or = 0;
    if (k > 30) {
        for (ll i = 0; i < k; i++) {
            cur_or |= v[i];
            for (ll j = 0; j < 30; j++)
                cnt[j] += (v[i] >> j) & 1;
        }
        ans = cur_or;
        for (ll i = k; i < n; i++) {
            cur_or |= v[i];
            for (ll j = 0; j < 30; j++) {
                cnt[j] += (v[i] >> j) & 1;
                cnt[j] -= (v[i - k] >> j) & 1;
                if (cnt[j] == 0)
                    cur_or &= ~(1ll << j);
            }
            ans ^= cur_or;
        }
    } else {
        deque<ll> dq;
        for (ll i = 0; i < n; i++) {
            dq.pb(v[i]);
            cur_or |= v[i];
            if (sz(dq) > k) {
                dq.pop_front();
                cur_or = 0;
                for (ll j : dq)
                    cur_or |= j;
            }
            if (i >= k - 1) ans ^= cur_or;
        }
    }
    cout << ans << '\n';

    return 0;
}
