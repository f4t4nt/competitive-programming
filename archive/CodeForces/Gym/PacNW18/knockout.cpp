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
#define x first
#define y second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)
#define FOB(x, b, e) for (auto x = b; x < e; x++)
#define FORE(x, C) for (auto &x : C)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

bool MAX = false;

vector<ld> p(13);
// [state][sum] = <ev, cut>
// [state][0] = <avg, 0>
map<ll, vector<pair<ld, ll>>> mem;

ll bit_to_ll(ll state) {
    ld res = 0;
    FOR (i, 10) if (state & (1 << i)) res = res * 10 + i;
    return res;
}

ll bit_to_sum(ll state) {
    ll res = 0;
    FOR (i, 10) if (state & (1 << i)) res += i;
    return res;
}

ld eval(ll state) {
    if (!mem.count(state)) {
        mem[state].resize(13, {(MAX ? -1e18 : 1e18), 0});
        FOR (x, 1 << 10) {
            if ((state & x) == x) {
                ll sum = bit_to_sum(x);
                if (1 >= sum || sum >= 13) continue;
                ld cur = eval(state ^ x);
                if (MAX == (mem[state][sum].x < cur)) mem[state][sum] = {cur, x};
            }
        }
        mem[state][0] = {0, 0};
        FOB (i, 1, 13) {
            if (abs(mem[state][i].x) == 1e18) mem[state][i] = {bit_to_ll(state), 0};
            mem[state][0].x += mem[state][i].x * p[i];
        }
    }
    return mem[state][0].x;
}

void output_res(pair<ld, ll> &res) {
    if (res.y == 0) cout << -1;
    else cout << bit_to_ll(res.y);
    cout << ' ' << fixed << setprecision(5) << res.x << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    p[0] = 1;
    FOR (_, 2) {
        auto tmp = p;
        fill(all(p), 0);
        FOB (d, 1, 7) FOR (i, 13) if (i + d < 13) p[i + d] += tmp[i] / 6;
    }

    str s; ll d1, d2, state = 0; cin >> s >> d1 >> d2;
    for (ch d : s) state |= 1 << (d - '0');
    MAX = false;
    mem.clear();
    eval(state);
    pair<ld, ll> res0 = mem[state][d1 + d2];
    MAX = true;
    mem.clear();
    eval(state);
    pair<ld, ll> res1 = mem[state][d1 + d2];
    output_res(res0);
    output_res(res1);

    return 0;
}