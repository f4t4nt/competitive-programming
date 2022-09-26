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

vector<int> getResult(vector<int> arrival, vector<int> street) {
    int n = arrival.size();
    vector<tuple<int, int, int>> cars;
    FOR(i, n) {
        cars.pb(mt(arrival[i], street[i], i));
    }
    ssort(cars);
    vector<int> result(n);
    queue<int> q0, q1;
    int time = 0;
    int i = 0;
    int last = 1;
    while (i < n || !q0.empty() || !q1.empty()) {
        while (i < n && get<0>(cars[i]) <= time) {
            if (get<1>(cars[i]) == 0) {
                q0.push(get<2>(cars[i]));
            } else {
                q1.push(get<2>(cars[i]));
            }
            i++;
        }
        if (!q1.empty() && (q0.empty() || last == 1)) {
            while (!q1.empty()) {
                result[q1.front()] = time;
                q1.pop();
                time++;
            }
            last = 1;
        } else if (!q0.empty() && (q1.empty() || last == 0)) {
            while (!q0.empty()) {
                result[q0.front()] = time;
                q0.pop();
                time++;
            }
            last = 0;
        } else if (i < n) {
            time = get<0>(cars[i]);
            last = 1;
        }
    }
    return result;
}

int main() {
    ll T;
    cin >> T;
    FOR(t, T) {
        ll n;
        cin >> n;
        vector<int> arrival(n);
        vector<int> street(n);
        FOR(i, n) {
            cin >> arrival[i];
        }
        FOR(i, n) {
            cin >> street[i];
        }
        vector<int> result = getResult(arrival, street);
        FOR(i, n) {
            cout << result[i] << '\n';
        }
    }
    return 0;
}