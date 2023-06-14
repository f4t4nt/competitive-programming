#include <bits/stdc++.h>

using namespace std;

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
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

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

ld get_delta(ld start, ld end, ld half_life) {
    return (log(start) - log(end)) / log(2) * half_life;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);   
    cout.tie(nullptr);

    ld s, t;
    ll n;
    cin >> s >> t >> n;
    vector<pair<ld, ld>> all_blades(n);
    FOR (i, n) {
        cin >> all_blades[i].first >> all_blades[i].second;
    }
    rsort(all_blades);
    if (all_blades[0].first < s) {
        cout << -1 << '\n';
        return 0;
    }
    vector<pair<ld, ld>> best_blades;
    best_blades.pb(all_blades[0]);
    ll i = 0;
    while (i < n && all_blades[i].first >= s) {
        if (best_blades[0].second > all_blades[i].second) {
            best_blades[0] = all_blades[i];
        }
        i++;
    }
    while (i < n && all_blades[i].first > t) {
        if (best_blades.back().second > all_blades[i].second) {
            best_blades.pb(all_blades[i]);
        }
        i++;
    }

    ld rv = 0;
    FOR (i, sz(best_blades) - 1) {
        rv += get_delta(s, best_blades[i + 1].first, best_blades[i].second);
        s = best_blades[i + 1].first;
    }
    rv += get_delta(s, t, best_blades.back().second);

    cout << setprecision(10) << rv << '\n';

    return 0;
}