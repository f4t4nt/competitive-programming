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
    ll t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        vector<ll> a(n), b(n);
        FOR (i, n) {
            cin >> a[i];
        }
        FOR (i, n) {
            cin >> b[i];
        }
        ll m;
        cin >> m;
        map<ll, ll> razors;
        FOR (i, m) {
            ll size;
            cin >> size;
            razors[size]++;
        }
        bool sanity_check = true;
        FOR (i, n) {
            if (a[i] < b[i]) {
                sanity_check = false;
                break;
            }
            if (a[i] != b[i]) {
                ll count = razors[b[i]];
                if (count == 0) {
                    sanity_check = false;
                    break;
                }
            }
        }
        if (!sanity_check) {
            cout << "NO\n";
            continue;
        }
        bool valid = true;
        stack<ll> current_razors;
        ll i = 0;
        while (i < n) {
            while (!current_razors.empty() && current_razors.top() < b[i]) {
                current_razors.pop();
            }
            if (a[i] != b[i]) {
                if (current_razors.empty() || current_razors.top() > b[i]) {
                    if (razors[b[i]] == 0) {
                        valid = false;
                        break;
                    }
                    current_razors.push(b[i]);
                    razors[b[i]]--;
                }
                a[i] = min(a[i], current_razors.top());
            }
            i++;
        }
        if (valid) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}