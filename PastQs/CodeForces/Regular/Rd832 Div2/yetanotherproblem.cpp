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

int main() {
    ll n, q;
    cin >> n >> q;
    vector<map<ll, set<ll>>> ref(2);
    vector<ll> a(n + 1), sums(n + 1), xors(n + 1);
    FOB(i, 1, n + 1) {
        cin >> a[i];
        sums[i] = sums[i - 1] + a[i];
        xors[i] = xors[i - 1] ^ a[i];
        ref[i % 2][xors[i]].insert(i);
    }
    vector<pair<ll, ll>> queries(q);
    FOR (i, q) {
        cin >> queries[i].first >> queries[i].second;
    }
    FORE (query, queries) {
        ll l = query.first, r = query.second;
        if (xors[r] ^ xors[l - 1]) {
            cout << "-1\n";
        } else {
            if (sums[r] - sums[l - 1] == 0) {
                cout << "0\n";
            } else {
                ll len = r - l + 1;
                if (len % 2 == 1) {
                    cout << "1\n";
                } else {
                    if (a[l] == 0 || a[r] == 0) {
                        cout << "1\n";
                    } else {
                        auto x = ref[l % 2][xors[l - 1]].lower_bound(l);
                        if (x != ref[l % 2][xors[l - 1]].end() && *x < r) {
                            cout << "2\n";
                        } else {
                            cout << "-1\n";
                        }
                    }
                }
            }
        }
    }
    return 0;
}