#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef complex<long double> cd;
typedef long double ld;
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
    tree_order_statistics_node_update
>;

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for(ll x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FORE(x, C) for(auto &x : C)
 
#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

void binsearch(ll lo, ll hi, ll y, vector<ll> &x, vector<bool> &ok) {
    if (lo > hi) return;
    ll mid = (lo + hi) / 2;
    if (x[mid] == y) {
        ok[mid] = true;
        return;
    }
    if (x[mid] < y) binsearch(mid + 1, hi, y, x, ok);
    else binsearch(lo, mid - 1, y, x, ok);
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m, a, c;
    cin >> n >> m >> a >> c;
    n++;
    vector<ll> x(n); cin >> x[0];
    FOB (i, 1, n) x[i] = (a * x[i - 1] + c) % m;
    vector<bool> ok(n);
    FOB (i, 1, n) binsearch(1, n - 1, x[i], x, ok);
    ll rv = accumulate(all(ok), 0LL);
    cout << rv << '\n';

    return 0;
}