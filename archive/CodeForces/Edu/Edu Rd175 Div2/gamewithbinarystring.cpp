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

template<typename T> using indexed_set = tree<
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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n; cin >> n;
    str s; cin >> s;
    vector<ll> pre(n + 1), ref = {0, 1, 1, -2};
    for (ll i = 0; i < n; i++)
        pre[i + 1] = pre[i] + (s[i] == '1' ? -3 : 1);    
    vector<indexed_set<pll>> sets(4);
    ll ans = 0;
    for (ll i = 0; i <= n; i++) {
        for (ll j = 0; j < 4; j++) {
            ll k = (i - j + 4) % 4;
            ll bound = pre[i] - ref[k];
            ans += sets[j].order_of_key({bound, -1});
        }
        sets[i % 4].insert({pre[i], i});
    }
    cout << ans << '\n';

    return 0;
}