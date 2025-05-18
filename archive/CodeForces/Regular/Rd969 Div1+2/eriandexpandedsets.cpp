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

template<typename T>
using indexed_set = tree<
    T,
    null_type,
    less<T>,
    rb_tree_tag,
    tree_order_statistics_node_update>;

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

struct SlidingGCD {
    stack<pll> l, r;

    void push(ll x) {
        ll g = r.empty() ? x : __gcd(r.top().first, x);
        r.push({g, x});
    }

    void pop() {
        if (l.empty()) {
            while (!r.empty()) {
                ll v = r.top().second; r.pop();
                ll g = l.empty() ? v : __gcd(l.top().first, v);
                l.push({g, v});
            }
        }
        assert(!l.empty());
        l.pop();
    }

    ll get() {
        ll gl = l.empty() ? 0 : l.top().first;
        ll gr = r.empty() ? 0 : r.top().first;
        return __gcd(gl, gr);
    }
};

bool good(ll g) { return g && (g & -g) == g; }

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t;  cin >> t;
    while(t--) {
        ll n; cin >> n;
        vector<ll> a(n);
        for (ll &x : a) cin >> x;
        n--;
        vector<ll> b(n), nxt(n);
        for (ll i = 0; i < n; i++) b[i] = abs(a[i + 1] - a[i]);
        {
            ll i = n - 1, j = n;
            while (i >= 0) {
                if (b[i]) j = i;
                nxt[i--] = j;
            }
        }
        SlidingGCD st;
        ll ans = 1,         // for last element
            l = 0, r = 0,   // window: [a_l, ..., a_r]
            cnt = 1;        // for first element
        // # of valid segments starting at i
        for (ll i = 0; i < n; i++) {
            if (nxt[i] == i) {
                while (l < i) st.pop(), l++;
                while (r <= n && !good(st.get())) st.push(b[r++]);
                ans += (n - r + 1) * cnt + 1;
                cnt = 1;
            } else {
                ans += nxt[i] - i + 1;
                cnt++;
                if (i >= r) st.push(b[r++]);
            }
        }
        cout << ans << '\n';
    }

    return 0;
}
