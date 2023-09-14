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

constexpr ll MAX = 1e6 + 1;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n;
    cin >> n;
    vector<ll> seq(n), cnt(MAX), del(MAX), mn(MAX);
    FOR (i, n) {
        str s;
        cin >> s;
        ll c = (s[0] == 's' ? 1 : -1);
        seq[i] = c * stoll(s.substr(1));
        ll idx = abs(seq[i]);
        cnt[idx]++;
        del[idx] += c;
        mn[idx] = min(mn[idx], del[idx]);
    }
    pair<ll, ll> rv = {0, -1};
    FOR (idx, MAX) {
        if (cnt[idx] > 0 && del[idx] == 0 && mn[idx] == 0) {
            rv.first++;
        }
    }
    ll cur = rv.first;
    FOR (i, n) {
        ll idx = abs(seq[i]);
        if (del[idx] != 0) {
            continue;
        }
        if (seq[i] > 0) {
            if (mn[idx] == 0) {
                cur--;
            }
            mn[idx]--;
        } else {
            if (mn[idx] == -1) {
                cur++;
            }
            mn[idx]++;
        }
        if (cur > rv.first) {
            rv = {cur, i};
        }
    }
    cout << rv.second + 2 << ' ' << rv.first << '\n';

    return 0;
}