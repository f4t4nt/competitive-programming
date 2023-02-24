#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ch = char;
using str = string;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define mp make_pair
#define mt make_tuple
#define flip(C) reverse(C.begin(), C.end())
#define ssort(C) sort(C.begin(), C.end())
#define rsort(C) sort(C.begin(), C.end(), greater<>())

#define FOR(x, e) for(ll x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FOI(x, e, i) for(ll x = 0; x < (ll) e; x += (ll) i)
#define FOBI(x, b, e, i) for(ll x = (ll) b; x < (ll) e; x += (ll) i)
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    map<str, ll> color_to_idx;
    color_to_idx["pink"] = 0;
    color_to_idx["blue"] = 1;
    vector<tuple<ll, ll, ld>> trades(n);
    FOR (i, n) {
        str color_u, color_v;
        cin >> color_u >> color_v;
        ld rate;
        cin >> rate;
        if (!color_to_idx.count(color_u)) {
            color_to_idx[color_u] = sz(color_to_idx);
        }
        if (!color_to_idx.count(color_v)) {
            color_to_idx[color_v] = sz(color_to_idx);
        }
        ll color_u_idx = color_to_idx[color_u], color_v_idx = color_to_idx[color_v];
        trades[i] = {color_u_idx, color_v_idx, rate};
    }

    vector<ld> max_quant(sz(color_to_idx), -1e18);
    max_quant[0] = 0;
    FOR (i, n) {
        ll &color_u = get<0>(trades[i]), &color_v = get<1>(trades[i]);
        ld rate = log2(get<2>(trades[i]));
        max_quant[color_u] = max(max_quant[color_u], max_quant[color_v] + rate);
    }
    
    if (max_quant[1] == -1e18) {
        cout << 0 << '\n';
    } else {
        cout << setprecision(16) << min(pow(2, max_quant[1]), (ld) 10) << '\n';
    }

    return 0;
}