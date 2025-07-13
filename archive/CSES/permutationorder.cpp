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

ll fact[21];

vector<ll> get_kth_state(ll n, ll k) { // 1-indexed
    vector<ll> state(n);
    vector<bool> used(n + 1);
    for (ll i = 0; i < n; i++) {
        for (ll j = 1; j <= n; j++) {
            if (used[j]) continue;
            ll cnt = fact[n - i - 1];
            if (cnt < k) {
                k -= cnt;
                continue;
            }
            state[i] = j;
            used[j] = true;
            break;
        }
    }
    return state;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    fact[0] = 1;
    for (ll i = 1; i <= 20; i++)
        fact[i] = fact[i - 1] * i;

    ll t; cin >> t;
    while (t--) {
        ll q, n; cin >> q >> n;
        if (q == 1) {
            ll k; cin >> k;
            auto perm = get_kth_state(n, k);
            for (ll x : perm) cout << x << ' ';
            cout << '\n';
        } else {
            vector<ll> perm(n);
            for (ll &x : perm) cin >> x;
            ll lo = 1, hi = fact[n];
            while (lo < hi) {
                ll mid = (lo + hi) / 2;
                auto state = get_kth_state(n, mid);
                if (state == perm) {
                    lo = mid;
                    break;
                }
                if (state < perm) lo = mid + 1;
                else hi = mid;
            }
            cout << lo << '\n';
        }
    }

    return 0;
}
