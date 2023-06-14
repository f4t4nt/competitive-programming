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

ll gcd(ll x, ll y) {
	if(!y) return x;
	else return gcd(y, x % y);
}

int main() {
    ll t;
    cin >> t;
    while(t--) {
        ll n;
        cin >> n;
        str s;
        cin >> s;
        vector<ll> p(n);
        FOR(i, n) {
            cin >> p[i];
            p[i]--;
        }
        vector<bool> v(n);
        vector<str> ref;
        FOR(i, n) {
            if(v[i]) {
                continue;
            } else {
                str tmp;
                tmp = s[i];
                v[i] = true;
                ll j = p[i];
                while(i != j) {
                    tmp += s[j];
                    v[j] = true;
                    j = p[j];
                }
                ref.pb(tmp);
            }
        }
        ll rv = 1;
        FORE(r, ref) {
            ll x = 1;
            str tmp = r.substr(1, sz(r) - 1) + r[0];
            while(tmp != r) {
                tmp = tmp.substr(1, sz(r) - 1) + tmp[0];
                x++;
            }
            rv = rv * x / gcd(rv, x);
        }
        cout << rv << '\n';
    }
    return 0;
}