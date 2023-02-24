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
        vector<ll> p(n), q(n);
        FOR(i, n) cin >> p[i];
        if(n == 1) {
            cout << "-1\n";
            continue;
        }
        deque<ll> ref;
        FOR(i, n) ref.push_back(i + 1);
        FOR(i, n - 2) {
            ll j = ref.front();
            ref.pop_front();
            if(p[i] == j) {
                ll k = ref.front();
                ref.pop_front();
                ref.push_front(j);
                q[i] = k;
            } else {
                q[i] = j;
            }
        }
        if(p[n - 2] != ref.front() && p[n - 1] != ref.back()) {
            q[n - 2] = ref.front();
            q[n - 1] = ref.back();
        } elif(p[n - 2] != ref.back() && p[n - 1] != ref.front()) {
            q[n - 2] = ref.back();
            q[n - 1] = ref.front();
        } else {
            cout << "-1\n";
            continue;
        }
        FOR(i, n) cout << q[i] << " ";
        cout << '\n';
    }
    return 0;
}