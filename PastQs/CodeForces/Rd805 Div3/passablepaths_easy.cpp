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

void parse(ll n, map<ll, ll> &a) {
    FOR(i, n) {
        ll x;
        cin >> x;
        a[x]++;
    }
    FORE(x, a) {
        ll y = x.first, z = x.second;
        while(y % 2 == 0) {
            y /= 2;
        }
        a[y] += z;
        a[x.first] -= z;
    }
    FORE(x, a) {
        if(x.second == 0) {
            a.erase(x.first);
        }
    }
}

int main() {
    ll t;
    cin >> t;
    while(t--) {
        ll n;
        cin >> n;
        map<ll, ll> a, b;
        parse(n, a);
        parse(n, b);
        bool valid = true;
        for(auto x = b.rbegin(); x != b.rend(); x++) {
            ll y = x->first, z = x->second;
            while(y && z > 0) {
                if(a[y] > z) {
                    a[y] -= z;
                    z = 0;
                } else {
                    z -= a[y];
                    a[y] = 0;
                }
                y /= 2;
            }
            b[x->first] = z;
            if(z > 0) {
                valid = false;
                break;
            }
        }
        if(valid) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}