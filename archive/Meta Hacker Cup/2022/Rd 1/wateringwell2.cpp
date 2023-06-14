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

// https://www.facebook.com/codingcompetitions/hacker-cup/2022/round-1/problems/B2

constexpr ll MOD = 1e9 + 7;

int main() {
    ll T;
    cin >> T;
    FOR(t, T) {
        ll N, Q, rv = 0, sumA2pB2 = 0, sumX2pY2 = 0, sumA = 0, sumX = 0, sumB = 0, sumY = 0;
        // sumA2pB2 = sum(A^2 + B^2)
        // sumX2pY2 = sum(X^2 + Y^2)
        // sumA = sum(A)
        // sumX = sum(X)
        // sumB = sum(B)
        // sumY = sum(Y)
        // rv = Q * sum(A^2 + B^2) + N * sum(X^2 + Y^2) - 2 * (sum(A) * sum(X) + sum(B) * sum(Y))
        cin >> N;
        vector<pair<ll, ll>> trees(N);
        FOR(i, N) {
            cin >> trees[i].first >> trees[i].second;
            sumA2pB2 += trees[i].first * trees[i].first + trees[i].second * trees[i].second;
            sumA += trees[i].first;
            sumB += trees[i].second;
            sumA2pB2 %= MOD;
            sumA %= MOD;
            sumB %= MOD;
        }
        cin >> Q;
        vector<pair<ll, ll>> wells(Q);
        FOR(i, Q) {
            cin >> wells[i].first >> wells[i].second;
            sumX2pY2 += wells[i].first * wells[i].first + wells[i].second * wells[i].second;
            sumX += wells[i].first;
            sumY += wells[i].second;
            sumX2pY2 %= MOD;
            sumX %= MOD;
            sumY %= MOD;
        }
        rv = (rv + sumA2pB2 * Q) % MOD;
        rv = (rv + sumX2pY2 * N) % MOD;
        rv = (rv - 2 * (sumA * sumX + sumB * sumY) % MOD + MOD) % MOD;
        cout << "Case #" << t + 1 << ": " << rv << '\n';
    }
    return 0;
}