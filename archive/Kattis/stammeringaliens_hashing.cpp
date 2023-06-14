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

constexpr ll MOD = 10000000002065383;

vector<ll> pow26(4e4 + 10);

ll hash_compute(ll last_hash, char in_char, char out_char, ll base) {
    return ((last_hash * 26 + (in_char - 'a') - (out_char - 'a') * base) % MOD + MOD) % MOD;
}

ll full_compute(str& s, ll st, ll end) {
    ll hash = 0;
    while (st < end) {
        hash = ((hash * 26 + (s[st] - 'a')) % MOD + MOD) % MOD;
        st++;
    }
    return hash;
}

ll helper2(str& s, ll len, ll m) {
    map<ll, vector<pair<ll, int>>> hashes;
    ll hash = 0;
    ll rv = -1, base = pow26[len];
    for(ll i = 0, j = 0; i <= sz(s) - len; i++) {
        for(; j < i + len; j++) {
            hash = hash_compute(hash, s[j], i > 0 ? s[i - 1] : 'a', base);
        }
        auto it = hashes.find(hash);
        if (it == hashes.end()) {
            hashes[hash] = vector<pair<ll, int>>();
            hashes[hash].pb(make_pair(i, 1));
        } else {
            bool matched = false;
            FORE(v, it->second) {
                if (memcmp(&s[i], &s[v.first], len) == 0) {
                    v.second++;

                    matched = true;
                    if (v.second >= m) {
                        rv = i;
                        break;
                    }
                }
            }
            if (!matched) {
                it->second.push_back(make_pair(i, 1));
            }
        }
    }
    return rv;
}

int main() {
    pow26[0] = 1;
    FOB(i, 1, sz(pow26)) {
        pow26[i] = (pow26[i - 1] * 26) % MOD;
    }
    while (true) {
        str m_str;
        getline(cin, m_str);
        ll m = stoll(m_str);
        if (m == 0) {
            break;
        }
        str s;
        getline(cin, s);
        ll lo = 0, hi = sz(s), v;
        if (m == 1) {
            cout << hi << ' ' << 0 << '\n';
            continue;
        }
        while (lo < hi) {
            ll mid = (lo + hi + 1) / 2;
            ll tv = helper2(s, mid, m);
            if (tv != -1) {
                lo = mid;
                v = tv;
            } else {
                hi = mid - 1;
            }
        }
        if (lo == 0) {
            cout << "none\n";
        } else {
            cout << lo << ' ' << v << '\n';
        }
    }
    return 0;
}