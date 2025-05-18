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

// https://codeforces.com/contest/1618/problem/F

ll binflip(ll x) {
    str s = "";
    while (x > 0) {
        s += (x % 2 == 0 ? '0' : '1');
        x /= 2;
    }
    ll rv = 0;
    FOR(i, s.size()) {
        rv *= 2;
        rv += (s[i] == '1' ? 1 : 0);
    }
    return rv;
}

int main() {
    ll x, y, sz = 1;
    cin >> x >> y;
    if(x == y) {
        cout << "YES\n";
        return 0;
    }
    queue<ll> bfs;
    set<ll> v;
    bfs.push(x);
    v.insert(x);
    bool valid = false;
    while(sz(bfs)) {
        ll a = bfs.front(), b = binflip(a * 2), c = binflip(a * 2 + 1);
        bfs.pop();
        if(a < 1e18) {
            v.insert(b);
            if(sz(v) > sz) {
                bfs.push(b);
                sz++;
                if(b == y) {
                    valid = true;
                    break;
                }
            }
            v.insert(c);
            if(sz(v) > sz) {
                bfs.push(c);
                sz++;
                if(c == y) {
                    valid = true;
                    break;
                }
            }
        }
    }
    if(valid) cout << "YES\n";
    else cout << "NO\n";
    return 0;
}