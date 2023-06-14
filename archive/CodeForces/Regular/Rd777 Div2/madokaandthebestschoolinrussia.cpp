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

// https://codeforces.com/contest/1647/problem/D

bool funkyfunc(ll &d, ll &sqrtd, ll &y)
{
    FOB(i, 2, sqrtd) if(d % i == 0 && ((y * i) % d != 0 || (y * (d / i)) % d != 0)) return false;
    return true;
}

int main()
{
    ll t;
    cin >> t;
    while(t--)
    {
        ll x, d;
        cin >> x >> d;
        if(x % (d * d) != 0) cout << "NO\n";
        else
        {
            // x = y *  d ^ e
            ll y = x, e = 0, sqrtd = sqrt(d) + 1, taud = 0;
            while(y % d == 0)
            { y /= d; e++; }
            ll sqrty = sqrt(y) + 1, tauy = 0;
            FOB(i, 1, sqrty)
            {
                if(y % i == 0)
                {
                    if(i * i == y) tauy += 1;
                    else tauy += 2;
                }
            }
            FOB(i, 1, sqrtd)
            {
                if(d % i == 0)
                {
                    if(i * i == d) taud += 1;
                    else taud += 2;
                }
            }
            if(tauy <= 2 && (e == 2 || taud <= 2)) cout << "NO\n";
            elif(tauy <= 2 && e == 3 && funkyfunc(d, sqrtd, y)) cout << "NO\n";
            else cout << "YES\n";
        }
    }
    return 0;
}