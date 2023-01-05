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

// https://open.kattis.com/problems/krotating

int main() {
    ll n, m, q;
    cin >> n >> m >> q;
    ll sqrtm = sqrt(m);
    map<ll, vector<ll>> all;
    vector<vector<ll>> cache(sqrtm + 1, vector<ll>(n));
    FOR (i, sqrtm + 1) {
        FOR (j, n) {
            cache[i][j] = j + 1;
        }
    }
    ll dirty = m + 1;
    while (q--) {
        ll a;
        cin >> a;
        if (a == 0) {
            ll k, x;
            cin >> k >> x;
            vector<ll> rotation(k);
            FOR (i, k) {
                cin >> rotation[i];
            }
            all[x] = rotation;
            dirty = min(dirty, x);
        } else {
            ll d, x;
            cin >> d >> x;
            if (dirty > x) {
                vector<ll> rv = cache[x / sqrtm];
                auto it = all.upper_bound(x / sqrtm * sqrtm);
                while (it != all.end() && it->first < x) {
                    ll tmp = rv[it->second[0] - 1];
                    FOR (i, sz(it->second) - 1) {
                        rv[it->second[i] - 1] = rv[it->second[i + 1] - 1];
                    }
                    rv[it->second.back() - 1] = tmp;
                }
                cout << rv[d - 1] << '\n';
            } else {
                vector<ll> rv = cache[(dirty - 1) / sqrtm];
                auto it = all.upper_bound((dirty - 1) / sqrtm * sqrtm);
                while (it != all.end() && it->first <= x) {
                    ll tmp = rv[it->second[0] - 1];
                    FOR (i, sz(it->second) - 1) {
                        rv[it->second[i] - 1] = rv[it->second[i + 1] - 1];
                    }
                    rv[it->second.back() - 1] = tmp;
                    cache[(it->first + sqrtm - 1) / sqrtm] = rv;
                    it++;
                }
                dirty = x + 1;
                cache[(x + sqrtm - 1) / sqrtm] = rv;
                cout << rv[d - 1] << '\n';
            }
        }
    }
    return 0;
}