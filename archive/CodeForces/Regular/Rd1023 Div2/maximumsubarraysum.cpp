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

void solve(ll n, ll k, str &s, vector<ll> &a) {
    ll cnt0 = 0;
    for (ll i = 0; i < n; i++) {
        if (s[i] == '0') {
            a[i] = -1e12;
            cnt0++;
        }
    }
    ll mn = 0, cur = 0, mx = a[0];
    for (ll i = 0; i < n; i++) {
        cur += a[i];
        if (cur - mn > mx) mx = cur - mn;
        if (cur < mn) mn = cur;
    }
    if (mx > k) {
        cout << "No\n";
    } elif (mx == k) {
        cout << "Yes\n";
        for (ll x : a) cout << x << ' ';
        cout << '\n';
    } elif (!cnt0) {
        cout << "No\n";
    } else {
        for (ll i = 0; i < n; i++) {
            if (a[i] == -1e12) {
                ll mxl = 0, suml = 0, mxr = 0, sumr = 0;
                for (ll j = i - 1; j >= 0; j--) {
                    suml += a[j];
                    mxl = max(mxl, suml);
                }
                for (ll j = i + 1; j < n && a[j] != -1e12; j++) {
                    sumr += a[j];
                    mxr = max(mxr, sumr);
                }
                a[i] = k - mxl - mxr;
                break;
            }
        }
        mn = 0, cur = 0, mx = a[0];
        for (ll i = 0; i < n; i++) {
            cur += a[i];
            if (cur - mn > mx) mx = cur - mn;
            if (cur < mn) mn = cur;
        }
        assert(mx == k);
        cout << "Yes\n";
        for (ll x : a) cout << x << ' ';
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n, k, cnt0 = 0; cin >> n >> k;
        str s; cin >> s;
        vector<ll> a(n);
        for (ll &x : a) cin >> x;
        solve(n, k, s, a);
    }

    return 0;
}
