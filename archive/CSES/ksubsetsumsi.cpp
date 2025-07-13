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

    ll n, k; cin >> n >> k;
    ll base = 0, cnt0 = 0;
    vector<ll> a;
    for (ll i = 0; i < n; i++) {
        ll x; cin >> x;
        if (x == 0) cnt0++;
        elif (x > 0) a.pb(x);
        else {
            base += x;
            a.pb(-x);
        }
    }
    ssort(a);
    ll dup = 1;
    for (ll i = 0; i < cnt0 && dup < k; i++)
        dup <<= 1;
    dup = min(dup, k);
    vector<ll> ans;
    auto push_many = [&](ll x) {
        for (ll i = 0; i < dup && sz(ans) < k; i++)
            ans.pb(x);
    };
    push_many(base);
    std::priority_queue<pll, vector<pll>, greater<pll>> pq;
    if (sz(a)) pq.push({base + a[0], 0});
    while (sz(ans) < k) {
        auto [x, i] = pq.top(); pq.pop();
        push_many(x);
        if (i + 1 < sz(a)) {
            pq.push({x - a[i] + a[i + 1], i + 1});
            pq.push({x + a[i + 1], i + 1});
        }
    }
    ssort(ans);
    for (ll x : ans) cout << x << ' ';
    cout << '\n';

    return 0;
}
