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

// #ifdef LOCAL
// #include "tester.cpp"
// #define main test_main
// extern istringstream fin;
// extern ostringstream fout;
// string test_file_name = "tests";
// #define cin fin
// #define cout fout
// #endif

// https://codeforces.com/contest/1697/problem/D

int main() {
    ll n, tmp0 = 0;
    cin >> n;
    map<ch, ll> ref0;
    vector<ch> rv(n);
    FOR(i, n) {
        ll tmp1;
        cout << "? 2 1 " << i + 1 << endl;
        cin >> tmp1;
        if(tmp1 > tmp0) {
            cout << "? 1 " << i + 1 << endl;
            cin >> rv[i];
            ref0[rv[i]] = i + 1;
            tmp0 = tmp1;
        } else {
            vector<pair<ll, ch>> ref1;
            FORE(r, ref0) ref1.pb(mp(r.second, r.first));
            ssort(ref1);
            ll lo = 0, hi = sz(ref1) - 1;
            while(lo != hi) {
                ll tmp2;
                ll mid = (lo + hi) / 2;
                cout << "? 2 " << ref1[mid].first + 1 << ' ' << i + 1 << endl;
                cin >> tmp2;
                if(tmp2 == tmp1 - mid - 1) lo = mid + 1; 
                else hi = mid;
            }
            rv[i] = ref1[lo].second;
            ref0[rv[i]] = i + 1;
        }
    }
    cout << "! ";
    FOR(i, n) cout << rv[i];
    cout << '\n';
    return 0;
}