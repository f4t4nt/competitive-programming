#include <algorithm>
#include <cmath>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <list>
#include <map>
#include <math.h>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <string>
#include <string.h>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>

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

constexpr ll MOD = 1e9 + 7;

ll solve(ll i, ll n, vector<ll> &w, vector<str> &words, vector<vector<ll>> &permute) {
    if (sz(words[i]) != n) {
        return 0;
    }
    vector<vector<pair<ll, ll>>> ref(51, vector<pair<ll, ll>>(26));
    FOR (j, n) {
        ref[w[j]][words[i][j] - 'a'].second++;
    }
    FORE (word, words) {
        if (word == words[i]) {
            continue;
        }
        ref[sz(word)][word[0] - 'a'].first++;
    }
    ll rv = 1;
    FOR (k, 51) {
        FOR (j, 26) {
            if (ref[k][j].first < ref[k][j].second) {
                return 0;
            }
            rv *= permute[ref[k][j].first][ref[k][j].second];
        }
    }
    return rv;
}

int main() {
    vector<vector<ll>> permute(51, vector<ll>(51));
    FOR (i, 51) {
        permute[i][0] = 1;
        FOB (j, 1, i + 1) {
            permute[i][j] = (permute[i][j - 1] * (i - j + 1)) % MOD;
        }
    }
    ll t;
    cin >> t;
    while (t--) {
        ll n, d;
        cin >> n;
        vector<ll> w(n);
        FOR (i, n) {
            cin >> w[i];
        }
        cin >> d;
        vector<str> words(d);
        FOR (i, d) {
            cin >> words[i];
        }
        ll rv = 0;
        FOR (i, n) {
            rv += solve(i, n, w, words, permute);
            rv %= MOD;
        }
        cout << rv << '\n';
    }
    return 0;
}