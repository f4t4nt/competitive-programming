#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;

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
#define FOB(x, b, e) for(auto x = b; x != e; x++)
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

vector<ll> mn(8e5), mx(8e5), lazy(8e5);

void push(ll i, ll l, ll r) {
    if (l == r || !lazy[i]) {
        return;
    }
    mx[2 * i] += lazy[i];
    mn[2 * i] += lazy[i];
    lazy[2 * i] += lazy[i];
    mx[2 * i + 1] += lazy[i];
    mn[2 * i + 1] += lazy[i];
    lazy[2 * i + 1] += lazy[i];
    lazy[i] = 0;
}

void update(ll lo, ll hi, ll val, ll i, ll l, ll r) {
    if (lo <= l && r <= hi) {
        mx[i] += val;
        mn[i] += val;
        lazy[i] += val;
        return;
    }
    push(i, l, r);
    ll m = (l + r) / 2;
    if (lo <= m) {
        update(lo, hi, val, 2 * i, l, m);
    }
    if (hi > m) {
        update(lo, hi, val, 2 * i + 1, m + 1, r);
    }
    mx[i] = max(mx[2 * i], mx[2 * i + 1]);
    mn[i] = min(mn[2 * i], mn[2 * i + 1]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n;
    cin >> n;
    FOR (i, n) {
        ll a, b;
        cin >> a >> b;
        if (b == 1) {
            update(1, a, 1, 1, 1, n);
        } else {
            update(1, a, -1, 1, 1, n);
        }
        if (mx[1] <= 0) {
            cout << "<\n";
        } elif (mn[1] >= 0) {
            cout << ">\n";
        } else {
            cout << "?\n";
        }
    }

    return 0;
}