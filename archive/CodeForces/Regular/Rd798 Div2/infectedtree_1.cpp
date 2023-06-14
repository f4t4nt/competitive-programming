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

int main() {
    ll t;
    cin >> t;
    while(t--) {
        ll n;
        cin >> n;
        vector<vector<ll>> e(n);
        e[0].pb(0);
        FOR(i, n - 1) {
            ll a, b;
            cin >> a >> b;
            e[a - 1].pb(b - 1);
            e[b - 1].pb(a - 1);
        }
        multimap<ll, ll> bfs;
        vector<bool> v(n);
        bfs.insert(mp(0, 0));
        v[0] = true;
        while(sz(bfs)) {
            auto p = *bfs.begin();
            auto x = p.first;
            auto y = p.second;
            bfs.erase(bfs.begin());
            if(y == -1) {
                cout << n - x << '\n';
                break;
            }
            FOR(i, sz(e[y])) {
                if(!v[e[y][i]]) {
                    bfs.insert(mp(
                        x + 1 + max(sz(e[y]) - 2, 0LL),
                        e[y][i]));
                    v[e[y][i]] = true;
                }
            }
            FOB(i, sz(e[y]), 3) bfs.insert(mp(x + 1 + max(sz(e[y]) - 1, 0LL), -1));
        }
    }
    return 0;
}