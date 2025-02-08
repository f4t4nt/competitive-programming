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

using indexed_set = tree<
    ll,
    null_type,
    less<ll>,
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
#define x first
#define y second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FOR1(x, e) for (ll x = 1; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

bool valid(str b, str tgt) {
    ll i = 0, j = 0;
    while (i < sz(b) && j < sz(tgt)) {
        if (b[i] == tgt[j]) j++;
        i++;
    }
    return j == sz(tgt);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    str a, b; ll c, d;
    cin >> a >> b >> c >> d;
    ll gcd_cd = __gcd(c, d);
    c /= gcd_cd, d /= gcd_cd;
    vector<ll> cnt_a(10), cnt_b(10);
    for (ch x : a) cnt_a[x - '0']++;
    for (ch x : b) cnt_b[x - '0']++;
    FOR (mask, 1 << sz(a)) {
        if (mask == 0) continue;
        str tmp = "";
        vector<ll> cnt_cur(10);
        FOR (i, sz(a)) {
            if (mask & (1 << i)) tmp += a[i];
            else cnt_cur[a[i] - '0']++;
        }
        if (tmp[0] == '0') continue;
        bool ok = true;
        FOR (i, 10) if (cnt_cur[i] > cnt_b[i]) {
            ok = false;
            break;
        }
        if (!ok) continue;
        ll aa = stoll(tmp), gcd_aac = __gcd(aa, c);
        aa /= gcd_aac;
        if (c != gcd_aac || d >= 1e18 / aa || aa >= 1e18 / d) continue;
        str tgt = to_string(aa * d);
        if (valid(b, tgt)) {
            cout << "possible\n" << tmp << ' ' << tgt << '\n';
            return 0;
        }
    }

    cout << "impossible\n";

    return 0;
}