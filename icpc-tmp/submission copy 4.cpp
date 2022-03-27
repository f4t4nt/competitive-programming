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

bool recurse(str s, vector<vector<ll>> &ref, vector<bool> c)
{
    ll i = sz(s);
    if(i == sz(ref[0]))
    { cout << s << '\n'; return true; }
    else
    {
        vector<bool> cf = c, ct = c;
        bool validf = true, validt = true;
        FOR(j, sz(c))
        {
            if(ref[j][i] == 1)
            {
                if(c[j]) validt = false;
                else ct[j] = true;
            }
            if(ref[j][i] == -1)
            {
                if(c[j]) validf = false;
                else cf[j] = true;
            }
            if(!validf && !validt) return false;
        }
        if(validf) if(recurse(s + "F", ref, cf)) return true;
        if(validt) if(recurse(s + "T", ref, ct)) return true;
        return false;
    }
}

int main()
{
    ll n, k;
    cin >> n >> k;
    vector<vector<ll>> ref(n, vector<ll>(k));
    FOR(i, n)
    {
        FOR(j, k)
        {
            char c;
            cin >> c;
            if(c == 'T') ref[i][j] = 1;
            elif(c == 'F') ref[i][j] = -1;
            elif(c == 'X') ref[i][j] = 0;
        }
    }
    vector<bool> c(n);
    if(!recurse("", ref, c)) cout << -1 << '\n';
    return 0;
}