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

constexpr ll MOD = 998244353;

struct DSU {
	vector<ll> e;
	DSU(ll N) { e = vector<ll>(N, -1); }
	ll get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
	bool same_set(ll a, ll b) { return get(a) == get(b); }
	ll size(ll x) { return -e[get(x)]; }
	bool unite(ll x, ll y) {
		x = get(x), y = get(y);
		if (x == y) return false;
		if (e[x] > e[y]) swap(x, y);
		e[x] += e[y]; e[y] = x;
		return true;
	}
};

ll pow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = (res * a) % MOD;
        }
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}

int main() {
    ll t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        vector<vector<ll>> ab_o(n, vector<ll>(2)), ab;
        FOR (i, n) {
            cin >> ab_o[i][0];
            ab_o[i][0]--;
        }
        FOR (i, n) {
            cin >> ab_o[i][1];
            ab_o[i][1]--;
        }
        ab = ab_o;
        bool valid = true;
        vector<set<ll>> options(n);
        FOR (i, n) {
            options[ab[i][0]].insert(i);
            if (ab[i][0] != ab[i][1]) {
                options[ab[i][1]].insert(i);
            }
        }
        queue<ll> q;
        FOR (i, n) {
            if (sz(options[i]) == 0) {
                valid = false;
                break;
            } elif (sz(options[i]) == 1) {
                q.push(i);
            }
        }
        while (!q.empty()) {
            ll i = q.front();
            q.pop();
            if (sz(options[i]) == 0) {
                valid = false;
                break;
            } elif (sz(options[i]) == 1) {
                ll j = *options[i].begin();
                ll tmp;
                if (ab[j][0] != i) {
                    tmp = ab[j][0];
                } elif (ab[j][1] != i) {
                    tmp = ab[j][1];
                } else {
                    continue;
                }
                options[tmp].erase(j);
                ab[j][0] = ab[j][1] = i;
                if (sz(options[tmp]) == 0) {
                    valid = false;
                    break;
                } elif (sz(options[tmp]) == 1) {
                    q.push(tmp);
                }
            }
        }
        if (!valid) {
            cout << "0\n";
            continue;
        }
        DSU dsu(n);
        ll extras = 0;
        FOR (i, n) {
            if (ab[i] == ab_o[i]) {
                if (ab[i][0] == ab[i][1]) {
                    extras++;
                } else {
                    dsu.unite(ab[i][0], ab[i][1]);
                }
            }
        }
        ll rotations = 0;
        FOR (i, n) {
            if (dsu.get(i) == i && dsu.size(i) > 1) {
                rotations++;
            }
        }
        ll rv1 = pow(n, extras), rv2 = pow(2, rotations);
        cout << (rv1 * rv2) % MOD << '\n';
    }
    return 0;
}