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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        str s; cin >> s;
        ll ans = n + (s[0] == '1'), del = (s[n - 1]=='1') - (s[0] == '1');
        for (ll i = 1; i < n; i++) ans += (s[i] != s[i - 1]);
        ll cnt01 = 0, cnt10 = 0;
        for (ll i = 1; i < n; i++) {
            if (s[i - 1] == '0' && s[i] == '1') cnt01++;
            if (s[i - 1] == '1' && s[i] == '0') cnt10++;
        }
        if (max(cnt01, cnt10) >= 2) del = min(del, -2LL);
        for (ll i = 1; i < n; i++) {
            ll t1 = s[0] != s[i],
                t2 = s[i - 1] != s[i],
                t3 = s[i - 1] == '1',
                t4 = s[0] == '1';
            del = min(del, t1 - t2 + t3 - t4);
        }
        for (ll i = 1; i < n; i++)
            del = min(del, (ll) (s[i - 1] != s[n - 1]) - (s[i - 1] != s[i]));
        del = min(del, 0LL);
        ans += del;
        cout << ans << '\n';
    }

    return 0;
}