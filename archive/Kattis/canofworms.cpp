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

// imma show YOU how great i am.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n; cin >> n;
    // {x, r}
    vector<tuple<ll, ll, ll>> cans(n);
    FOR (i, n) {
        ll x, r;
        cin >> x >> r;
        cans[i] = {x, r, i};
    }
    ssort(cans);
    vector<ll> mn(n), mx(n);
    iota(all(mn), 0);
    iota(all(mx), 0);
    bool mod = true;
    stack<ll> stk;
    auto upd = [&](ll i) {
        while (!stk.empty() && abs(get<0>(cans[stk.top()]) - get<0>(cans[i])) <= get<1>(cans[i])) {
            ll j = stk.top();
            stk.pop();
            if (mx[i] < mx[j]) {
                mx[i] = mx[j];
                mod = true;
            }
            if (mn[i] > mn[j]) {
                mn[i] = mn[j];
                mod = true;
            }
        }
        stk.push(i);
    };
    while (mod) {
        mod = false;
        FORR (i, n) upd(i);
        stk = stack<ll>();
        FOR (i, n) upd(i);
        stk = stack<ll>();
    }
    vector<ll> rv(n);
    FOR (i, n) {
        ll j = get<2>(cans[i]);
        rv[j] = mx[i] - mn[i] + 1;
    }
    FORE (x, rv) cout << x << ' ';
    cout << '\n';

    return 0;
}