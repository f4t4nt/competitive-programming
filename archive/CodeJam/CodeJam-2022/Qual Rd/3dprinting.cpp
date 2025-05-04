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

// https://codingcompetitions.withgoogle.com/codejam/round/0000000000876ff1/0000000000a4672b

int main()
{
    ll T;
    cin >> T;
    FOR(t, T)
    {
        vector<ll> rv(4, 1e18);
        FOR(i, 3)
        {
            FOR(j, 4)
            {
                ll x;
                cin >> x;
                rv[j] = min(rv[j], x);
            }
        }
        ll S = 0;
        FOR(i, 4)
        {
            S += rv[i];
            if(S >= 1e6)
            {
                ll d = S - 1e6;
                rv[i] -= d;
                FOB(j, i + 1, 4) rv[j] = 0;
                S = 1e6;
                break;
            }
        }
        cout << "Case #" << t + 1 << ": ";
        if(S < 1e6) cout << "IMPOSSIBLE";
        else FOR(i, 4) cout << rv[i] << " ";
        cout << '\n';
    }
    return 0;
}