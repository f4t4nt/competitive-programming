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
    pld,
    null_type,
    less<pld>,
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

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
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

str REF = "NANACACB";

vector<vector<ll>> partitions(ll cnt, ll n) {
    if (n == 1) return {{cnt}};
    vector<vector<ll>> res;
    for (ll i = 0; i <= cnt; i++) {
        auto parts = partitions(cnt - i, n - 1);
        for (auto &part : parts) {
            part.pb(i);
            res.pb(part);
        }
    }
    return res;
}

ll get_max(ll n) {
    ll tmp[3] = {n / 3, n / 3 + (n % 3 > 0), n / 3 + (n % 3 > 1)};
    return tmp[0] * tmp[1] * tmp[2];
}

ll get_k(str &s) {
    vector<ll> dp(3, 0);
    for (ch c : s) {
        if (c == 'N') dp[0]++;
        elif (c == 'A') dp[1] += dp[0];
        elif (c == 'C') dp[2] += dp[1];
    }
    return dp[2];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, k; cin >> n >> k;
    str s; cin >> s;
    ll n2 = n;
    for (ch &c : s) if (c != 'N' && c != 'A' && c != 'C' && c != '?') n2--;
    if (k > get_max(n2) || k < get_k(s)) {
        cout << -1 << '\n';
        return 0;
    }
    ll cnt = 0;
    FOR (i, n) if (s[i] == '?') cnt++;
    auto parts = partitions(cnt, sz(REF));
    shuffle(all(parts), rng);
    for (auto &part : parts) {
        if (k > get_max(n2 - part.back())) continue;
        str s2 = s;
        ll j = 0;
        FOR (i, n) {
            if (s2[i] == '?') {
                FOR (k, sz(REF)) {
                    if (part[k]) {
                        s2[i] = REF[k];
                        part[k]--;
                        break;
                    }
                }
            }
        }
        if (get_k(s2) == k) {
            cout << s2 << '\n';
            return 0;
        }
    }
    cout << -1 << '\n';

    return 0;
}

/*
=
18 0
COUNTINGSATELLITES
=
COUNTINGSATELLITES
=
27 398
???????????????????????????
=
NNNNNNNNNNNNNNNNAANAACACCCC
=
26 459
??????????????????????????
=
NNNNNNNNNNNNANAAACCCCCCCCC
=
14 91
??????????????
=
NNNNANAAACACCC
=
13 193
?????????????
=
-1
=
5 4
?????
=
NNAAC
=
40 2197
????????????????????????????????????????
=
idk
=
40 2366
????????????????????????????????????????
=
idk
=
40 2367
????????????????????????????????????????
=
idk
=
22 2
N??A??????C???????????
=
NOTANOTHERCONSTRUCTIVE
=
2 1
??
=
-1
=
4 1
???C
=
BNAC
=
4 1
??C?
=
NACB
*/