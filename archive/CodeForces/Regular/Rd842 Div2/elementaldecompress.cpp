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
        vector<ll> a(n), p(n), q(n);
        vector<vector<ll>> ref(n + 1);
        FOR (i, n) {
            cin >> a[i];
            ref[a[i]].pb(i);
        }
        bool sanity_check = true;
        FOR (i, n) {
            if (sz(ref[i]) > 2) {
                sanity_check = false;
                break;
            }
        }
        if (!sanity_check || sz(ref[n]) == 0 || sz(ref[0]) == 2) {
            cout << "NO\n";
            continue;
        }
        vector<bool> p_used(n + 1, false), q_used(n + 1, false);
        set<pair<ll, ll>> empty_locations;
        bool valid = true;
        for (ll i = n; i > 0; i--) {
            if (sz(ref[i]) == 0) {
                if (sz(empty_locations) < 2) {
                    valid = false;
                    break;
                } else {
                    FOR (_, 2) {
                        auto it = empty_locations.begin();
                        ll idx = it->second;
                        empty_locations.erase(it);
                        if (p[idx] == 0) {
                            p[idx] = i;
                            p_used[i] = true;
                        } else {
                            q[idx] = i;
                            q_used[i] = true;
                        }
                    }
                }
            } elif (sz(ref[i]) == 1) {
                ll idx = ref[i][0];
                p[idx] = i;
                p_used[i] = true;
                q[idx] = i;
                q_used[i] = true;
            } else {
                ll idx1 = ref[i][0], idx2 = ref[i][1];
                p[idx1] = i;
                p_used[i] = true;
                q[idx2] = i;
                q_used[i] = true;
                empty_locations.insert(mp(i, idx1));
                empty_locations.insert(mp(i, idx2));
            }
        }
        if (!valid) {
            cout << "NO\n";
            continue;
        } else {
            cout << "YES\n";
            FOR (i, n) {
                cout << p[i] << " ";
            }
            cout << "\n";
            FOR (i, n) {
                cout << q[i] << " ";
            }
            cout << "\n";
        }
    }
    return 0;
}