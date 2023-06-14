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

// https://codeforces.com/contest/1657/problem/D

int main()
{
    ll n, C, m;
    cin >> n >> C;
    vector<ll> a(n), c(n);
    FOR(i, n)
    {
        ll d, h;
        cin >> c[i] >> d >> h;
        a[i] = d * h;
    }
    cin >> m;
    vector<ll> b(m);
    FOR(i, m)
    {
        ll d, h;
        cin >> d >> h;
        b[i] = d * h;
    }
    vector<ll> ref(C + 1);
    FOR(i, n) ref[c[i]] = max(ref[c[i]], a[i]);
    FOB(i, 1, C + 1) FOB(j, 2, C / i + 1) ref[j * i] = max(ref[j * i], j * ref[i]);
    FOR(i, C) ref[i + 1] = max(ref[i + 1], ref[i]);
    FOR(i, m)
    {
        if(ref[C] <= b[i]) cout << "-1 ";
        else
        {
            ll lo = 1, hi = C;
            while(hi - lo > 0)
            {
                ll mid = (hi + lo) / 2;
                if(ref[mid] <= b[i]) lo = mid + 1;
                else hi = mid;
            }
            cout << lo << ' ';
        }
    }
    cout << '\n';
    return 0;
}