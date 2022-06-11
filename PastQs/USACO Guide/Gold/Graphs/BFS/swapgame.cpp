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

// https://cses.fi/problemset/task/1670/

int main() {
    vector<ll> pow9(10);
    pow9[0] = 1;
    FOR(i, 9) pow9[i + 1] = pow9[i] * 9;
    ll s = 0, t = 0;
    FOR(i, 9) {
        ll x;
        cin >> x;
        s += (x - 1) * pow9[i];
    }
    FOR(i, 9) t += i * pow9[i];
    map<ll, ll> d;
    vector<bool> v(pow9[9]);
    queue<ll> bfs;
    d[s] = 0;
    v[s] = true;
    bfs.push(s);
    while(sz(bfs)) {
        ll x = bfs.front(), y;
        bfs.pop();
        if(x == t) break;
        FOR(i, 9) {
            y = x;
            if(i % 3 == 2) continue;
            ll a = x / pow9[i] % 9, b = x / pow9[i + 1] % 9;
            y -= a * pow9[i] + b * pow9[i + 1];
            y += b * pow9[i] + a * pow9[i + 1];
            if(!v[y]) {
                v[y] = true;
                d[y] = d[x] + 1;
                bfs.push(y);
            }
        }
        FOR(i, 6) {
            y = x;
            ll a = x / pow9[i] % 9, b = x / pow9[i + 3] % 9;
            y -= a * pow9[i] + b * pow9[i + 3];
            y += b * pow9[i] + a * pow9[i + 3];
            if(!v[y]) {
                v[y] = true;
                d[y] = d[x] + 1;
                bfs.push(y);
            }
        }
    }
    cout << d[t] << '\n';
    return 0;
}