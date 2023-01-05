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

bool check(ll &i, ll tol, ll &n, vector<ll> &s, vector<bool> &visited) {
    tol += s[i];
    ll left = (i - 1 + n) % n, right = (i + 1) % n;
    while (left != right && (s[left] <= tol || s[right] <= tol)) {
        if (s[left] <= tol) {
            tol += s[left];
            visited[left] = true;
            left = (left - 1 + n) % n;
        } elif (s[right] <= tol) {
            tol += s[right];
            visited[right] = true;
            right = (right + 1) % n;
        }
    }
    return left == right && s[left] <= tol;
}

bool valid(ll &tol, ll &n, vector<ll> &s) {
    vector<bool> visited(n, false);
    FOR (i, n) {
        if (!visited[i] && s[i] <= tol && check(i, tol, n, s, visited)) {
            return true;
        }
    }
    return false;
}

int main() {
    ll n, lo = 0, hi = 0;
    cin >> n;
    vector<ll> s(n);
    FOR (i, n) {
        cin >> s[i];
        hi = max(hi, s[i]);
    }
    while (lo < hi) {
        ll tol = (lo + hi) / 2;
        if (valid(tol, n, s)) {
            hi = tol;
        } else {
            lo = tol + 1;
        }
    }
    cout << lo << '\n';
    return 0;
}