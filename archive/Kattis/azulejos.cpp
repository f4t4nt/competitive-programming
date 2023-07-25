#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using db = double;
using cd = complex<double>;
using ld = long double;
using ch = char;
using str = string;

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

bool solve(
    vector<multiset<pair<ll, ll>>> &s_front,
    vector<multiset<pair<ll, ll>>> &s_back,
    vector<ll> &rv_front,
    vector<ll> &rv_back
) {
    ll n = sz(s_front);
    ll m = sz(s_back);
    ll i = 0, j = 0;
    while (i < n && j < m) {
        if (sz(s_front[i]) == 0) {
            i++;
            continue;
        } elif (sz(s_back[j]) == 0) {
            j++;
            continue;
        } elif (sz(s_front[i]) > sz(s_back[j])) {
            FORE (x, s_back[j]) {
                rv_back.pb(x.second);
                // find largest element y in s_front[i] s.t. y.first < x.first
                auto it = s_front[i].lower_bound({x.first, -1});
                if (it == s_front[i].begin()) {
                    return false;
                }
                it--;
                rv_front.pb(it->second);
                s_front[i].erase(it);
            }
            s_back[j].clear();
        } else {
            FORE (x, s_front[i]) {
                rv_front.pb(x.second);
                // find smallest element y in s_back[j] s.t. y.first > x.first
                auto it = s_back[j].upper_bound({x.first, 1e18});
                if (it == s_back[j].end()) {
                    return false;
                }
                rv_back.pb(it->second);
                s_back[j].erase(it);
            }
            s_front[i].clear();
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n;
    cin >> n;
    vector<tuple<ll, ll, ll>> front(n), back(n);
    FOR (i, n) {
        front[i] = {0, 0, i};
        back[i] = {0, 0, i};
    }
    FOR (i, n) cin >> get<0>(back[i]);
    FOR (i, n) cin >> get<1>(back[i]);
    FOR (i, n) cin >> get<0>(front[i]);
    FOR (i, n) cin >> get<1>(front[i]);
    ssort(front);
    ssort(back);
    vector<multiset<pair<ll, ll>>> s_front = {{{get<1>(front[0]), get<2>(front[0])}}},
        s_back = {{{get<1>(back[0]), get<2>(back[0])}}};
    FOB (i, 1, n) {
        if (get<0>(front[i]) == get<0>(front[i - 1])) {
            s_front.back().insert({get<1>(front[i]), get<2>(front[i])});
        } else {
            s_front.pb({{get<1>(front[i]), get<2>(front[i])}});
        }
        if (get<0>(back[i]) == get<0>(back[i - 1])) {
            s_back.back().insert({get<1>(back[i]), get<2>(back[i])});
        } else {
            s_back.pb({{get<1>(back[i]), get<2>(back[i])}});
        }
    }
    vector<ll> rv_front, rv_back;
    bool ok = solve(s_front, s_back, rv_front, rv_back);
    if (ok) {
        assert(sz(rv_front) == n && sz(rv_back) == n);
        FORE (x, rv_back) cout << x + 1 << ' ';
        cout << '\n';
        FORE (x, rv_front) cout << x + 1 << ' ';
        cout << '\n';
    } else {
        cout << "impossible\n";
    }

    return 0;
}