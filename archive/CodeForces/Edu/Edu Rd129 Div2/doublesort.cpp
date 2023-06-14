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
        vector<pair<ll, ll>> ab(n), rv;
        FOR(i, n) cin >> ab[i].first;
        FOR(i, n) cin >> ab[i].second;
        FOR(i, n) {
            ll j = i;
            FORR(k, j) {
                if(ab[k] > ab[j]) {
                    swap(ab[k], ab[j]);
                    rv.pb({k + 1, j + 1});
                    j--;
                } else break;
            }
        }
        bool valid = true;
        FOB(i, 1, n) {
            if(ab[i].second < ab[i - 1].second) {
                valid = false;
                break;
            }
        }
        if(valid) {
            cout << sz(rv) << '\n';
            FORE(r, rv) cout << r.first << " " << r.second << '\n';
        } else cout << "-1\n";
    }
    return 0;
}