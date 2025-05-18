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

void manacher(str &s, vector<ll> &ans) {
    str t = "$#";
    for (ch c : s) t += c, t += '#';
    ll n = sz(t);
    ll center = 0, max_rad = -1, rad;
    vector<ll> p(n);
    for (ll i = 1; i < n; i++) {
        if (i <= max_rad) rad = min(p[2 * center - i], max_rad - i);
        else rad = 0;
        while (i - rad - 1 >= 0 && i + rad + 1 < n && t[i - rad - 1] == t[i + rad + 1]) {
            rad++;
            ll end = (i + rad) / 2 - 1;
            ans[end] = max(ans[end], rad);
        }
        p[i] = rad;
        if (i + rad > max_rad) {
            center = i;
            max_rad = i + rad;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    str s; cin >> s;
    vector<ll> ans(sz(s));
    manacher(s, ans);
    for (ll x : ans) cout << x << ' ';
    cout << '\n';

    return 0;
}
