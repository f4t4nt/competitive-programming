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
#include <tuple>
#include <uNOrdered_set>
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

#define FOR(x, e) for(ll  x = 0; x < (ll) e; x++)
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

void search(ll i, vector<ll> &rv, vector<vector<ll>> &g, vector<bool> &v) {
    if(i == rv[0]) {
        return;
    } elif(v[i] == true) {
        rv.clear();
        return;
    } else {
        ll j = -1;
        rv.pb(i);
        v[i] = true;
        FORE(x, g[i]) {
            if(x != rv[sz(rv) - 2]) {
                j = x;
                break;
            }
        }
        if(j == -1) {
            rv.clear();
            return;
        } else {
            search(j, rv, g, v);
        }
    }
}

int main() {
    ll t;
    cin >> t;
    while(t--) {
        ll n;
        cin >> n;
        vector<pair<ll, ll>> d(n);
        vector<vector<ll>> g(n);
        bool valid = true;
        FOR(i, n) {
            cin >> d[i].first >> d[i].second;
            d[i].first--;
            d[i].second--;
            if(d[i].first == d[i].second) {
                valid = false;
            } else {
                g[d[i].first].pb(d[i].second);
                g[d[i].second].pb(d[i].first);
            }
        }
        if(!valid) {
            cout << "NO\n";
            continue;
        }
        FOR(i, n) {
            if(sz(g[i]) > 2) {
                valid = false;
                break;
            }
        }
        if(!valid) {
            cout << "NO\n";
            continue;
        }
        vector<bool> v(n);
        FOR(i, n) {
            if(sz(g[i]) == 2 && !v[i]) {
                v[i] = true;
                vector<ll> tmp = {i};
                search(g[i][0], tmp, g, v);
                if(sz(tmp) % 2 == 1) {
                    valid = false;
                    break;
                }
            }
        }
        if(!valid) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
    }
    return 0;
}