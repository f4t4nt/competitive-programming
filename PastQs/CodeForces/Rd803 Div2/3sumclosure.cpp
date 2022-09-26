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

int main() {
    ll t;
    cin >> t;
    while(t--) {
        ll n, pos = 0, neg = 0, zero = 0;
        cin >> n;
        set<ll> s;
        vector<ll> a(n);
        FOR(i, n) {
            cin >> a[i];
            s.insert(a[i]);
            if(a[i] > 0) {
                pos++;
            } elif(a[i] < 0) {
                neg++;
            } else {
                zero++;
            }
        }
        ssort(a);
        if(n < 5) {
            bool valid = true;
            FOR(i, n) {
                FOB(j, i + 1, n) {
                    FOB(k, j + 1, n) {
                        valid &= s.find(a[i] + a[j] + a[k]) != s.end();
                    }
                }
            }
            if(valid) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        } elif(pos == 0 && neg == 0) {
            cout << "YES\n";
        } elif(pos == 1 && neg == 1 && a[0] == -a[n - 1]) {
            cout << "YES\n";
        } elif(pos + neg == 1) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}