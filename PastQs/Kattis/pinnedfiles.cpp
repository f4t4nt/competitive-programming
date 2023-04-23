#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using cd = complex<double>;
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll p0, u0;
    cin >> p0 >> u0;
    ll n = p0 + u0;
    vector<vector<ll>> a0({vector<ll>(p0), vector<ll>(u0)}), a1(2);
    FOR (i, p0) {
        cin >> a0[0][i];
        a0[0][i]--;
    }
    FOR (i, u0) {
        cin >> a0[1][i];
        a0[1][i]--;
    }
    ll p1, u1;
    cin >> p1 >> u1;
    a1[0].resize(p1);
    a1[1].resize(u1);
    FOR (i, p1) {
        cin >> a1[0][i];
        a1[0][i]--;
    }
    FOR (i, u1) {
        cin >> a1[1][i];
        a1[1][i]--;
    }
    vector<ll> ref(n);
    vector<pair<ll, ll>> pos(n), tar(n);
    FOR (i, p1) {
        a1[0][i] = ref[a1[0][i]] = i;
        tar[i] = {0, i};
    }
    FOR (i, u1) {
        a1[1][i] = ref[a1[1][i]] = i + p1;
        tar[i + p1] = {1, i};
    }
    FOR (i, p0) {
        a0[0][i] = ref[a0[0][i]];
        pos[a0[0][i]] = {0, i};
    }
    FOR (i, u0) {
        a0[1][i] = ref[a0[1][i]];
        pos[a0[1][i]] = {1, i};
    }

    ll rv = 0;
    FOR (i, n) {
        if (pos[i].first != tar[i].first) {
            rv++;
            auto it = find(all(a0[pos[i].first]), i);
            a0[pos[i].first].erase(it);
        }
    }
    ll x = 0;
    FOR (i, sz(a0[0])) {
        if (a0[0][i] == x) {
            x++;
        } else {
            rv += 2;
        }
    }
    x = n - 1;
    FORR (i, sz(a0[1])) {
        if (a0[1][i] == x) {
            x--;
        } else {
            rv += 2;
        }
    }
    cout << rv << '\n';

    return 0;
}