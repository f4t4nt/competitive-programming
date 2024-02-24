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
    pair<ll, ll>,
    null_type,
    less<pair<ll, ll>>,
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

set<vector<ll>> ans;

bool ok(ll i, vector<ll> &num, vector<ll> &rv) {
    ll tmp = 0;
    FOR (j, i + 1) {
        ll k = i - j;
        tmp += rv[j] * rv[k];
    }
    return tmp % 10 == num[i];
}

void dfs(ll i, ll &n, vector<ll> &num, vector<ll> &rv) {
    if (i == n) {
        ans.insert(rv);
        return;
    }
    FOR (d, 10) {
        rv[i] = d;
        if (ok(i, num, rv)) dfs(i + 1, n, num, rv);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ans.clear();

    str s; cin >> s; flip(s);
    ll n = sz(s);
    vector<ll> num(n);
    FOR (i, n) num[i] = s[i] - '0';
    vector<ll> rv(n);
    dfs(0, n, num, rv);
    if (sz(ans) == 0) cout << -1 << '\n';
    else {
        rv = vector<ll>(25, 9);
        for (auto tmp : ans) {
            flip(tmp);
            rv = min(rv, tmp);
        }
        ll idx = 0;
        while (rv[idx] == 0) idx++;
        FOB (i, idx, n) cout << rv[i];
        cout << '\n';
    }

    return 0;
}