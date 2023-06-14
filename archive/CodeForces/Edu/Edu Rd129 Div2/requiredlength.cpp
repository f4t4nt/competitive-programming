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

bool onezero(ll x) {
    while(x) {
        if(x % 10 > 1) return false;
        x /= 10;
    }
    return true;
}

ll numDigit(ll x) {
    ll rv = 0;
    while(x > 0) {
        x /= 10;
        rv++;
    }
    return rv;
}

vector<ll> digits(ll x) {
    vector<ll> rv;
    while(x > 0) {
        rv.pb(x % 10);
        x /= 10;
    }
    return rv;
}

int main() {
    ll n, x, rv;
    cin >> n >> x;
    if(numDigit(x) == n) cout << "0\n";
    elif(onezero(x)) cout << "-1\n";
    else {
        ll rv = 0;
        set<ll> g0;
        g0.insert(x);
        while(numDigit(*g0.rbegin()) < n) {
            set<ll> g1;
            FORE(a, g0) {
                vector<ll> d = digits(a);
                FORE(b, d) g1.insert(a * b);
            }
            ll i = 0;
            auto it = g1.rbegin();
            g0.clear();
            while(i < 1000 && it != g1.rend()) {
                g0.insert(*it);
                it++;
                i++;
            }
            rv++;
        }
        cout << rv << '\n';
    }   
    return 0;
}