#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ch = char;
using str = string;

#define pb pugsh_back
#define ins insert
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

bool valid(ll x, ll &n, ll &c, vector<ll> &w, vector<vector<ll>> &knapsack) {
    ll curr_x = x, curr_n = n, w_i = sz(w) - 1;
    while (curr_x > 0 && w_i >= 0 && knapsack[curr_n][curr_x] == w[w_i]) {
        w_i--;
        curr_x -= knapsack[curr_n][curr_x];
        curr_n--;
    }
    if (w_i == -1) {
        return true;
    }
    if (x + w[w_i] > c) {
        return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, c;
    cin >> n >> c;
    vector<ll> w(n);
    FOR (i, n) {
        cin >> w[i];
    }
    rsort(w);

    vector<vector<ll>> knapsack(n + 1, vector<ll>(c + 1));
    knapsack[0][0] = -1;
    FOR (i, n) {
        knapsack[i + 1] = knapsack[i];
        FOR (x, c + 1) {
            if (x + w[i] > c) {
                break;
            }
            if (knapsack[i][x] != 0) {
                knapsack[i + 1][x + w[i]] = w[i];
            }
        }
    }

    ll rv = 1;
    while (rv <= c && (knapsack[n][rv] == 0 || !valid(rv, n, c, w, knapsack))) {
        rv++;
    }
    assert(rv <= c);
    cout << rv << '\n';

    return 0;
}