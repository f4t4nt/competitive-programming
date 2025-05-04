#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef complex<long double> cd;
typedef long double ld;
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
#define sz(C) (ll)C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
// #define x first
// #define y second

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

bool eval(ll n, vector<ll> &pre) {
    ll mn = pre[1], mx = pre[1];
    for (ll i = 2; i < n; i++) {
        // 011
        if (pre[i] - mn >= 0 && pre[n] - pre[i] >= 0) {
            return true;
        }
        // 101
        if (mx >= 0 && pre[n] - pre[i] >= 0) {
            return true;
        }
        mn = min(mn, pre[i]);
        mx = max(mx, pre[i]);
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n, k; cin >> n >> k;
        vector<ll> a(n), pre(n + 1);
        for (ll i = 0; i < n; i++) {
            cin >> a[i];
            a[i] = (a[i] <= k) ? 1 : -1;
            pre[i + 1] = pre[i] + a[i];
        }
        bool ok = eval(n, pre);
        if (!ok) {
            flip(a);
            for (ll i = 0; i < n; i++)
                pre[i + 1] = pre[i] + a[i];
            ok = eval(n, pre);
        }
        cout << (ok ? "YES\n" : "NO\n");
    }

    return 0;
}