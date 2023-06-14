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
    // ifstream cin("dishes.in");
    // ofstream cout("dishes.out");

    ll n;
    cin >> n;
    vector<ll> p(n);
    FOR (i, n) {
        cin >> p[i];
    }
    vector<pair<ll, stack<ll>>> q;
    ll rv = 0;
    while (rv < n) {
        if (q.empty()) {
            q.pb(mp(p[rv], stack<ll>()));
            q.back().second.push(p[rv]);
        } else {
            ll i = 0;
            while (i < sz(q) && q[i].first < p[rv]) {
                i++;
            }
            bool exit = false;
            if (i == sz(q)) {
                q.pb(mp(p[rv], stack<ll>()));
                q.back().second.push(p[rv]);
            } elif (q[i].second.top() > p[rv]) {
                q[i].second.push(p[rv]);
            } else {
                break;
            }
        }
        rv++;
    }
    ll tmp = 0;
    while (rv < n && p[rv] > tmp) {
        while (q[0].first < p[rv]) {
            tmp = q[0].first;
            q.erase(q.begin());
        }
        while (!q[0].second.empty() && q[0].second.top() < p[rv]) {
            tmp = q[0].second.top();
            q[0].second.pop();
        }
        if (q[0].second.empty()) {
            q.erase(q.begin());
        }
        q[0].second.push(p[rv]);
        rv++;
    }
    cout << rv << '\n';
    return 0;
}