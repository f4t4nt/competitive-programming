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
using fl = long double;
using ch = char;
using str = string;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define flip(C) reverse(C.begin(), C.end())
#define ssort(C) sort(C.begin(), C.end())
#define rsort(C) sort(C.begin(), C.end(), greater<>())
#define max_elem(C) *max_element(C.begin(), C.end())
#define min_elem(C) *min_element(C.begin(), C.end())
#define contains(C, x) find(C.begin(), C.end(), x) != C.end()

#define FOR(x, e) for(ll  x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = (ll) b; x != (ll) e; x++)
#define FOE(x, e, b) for(auto x = (ll) e - 1; x != (ll) b; x--)
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

// https://codeforces.com/contest/1644/problem/A

int main()
{
    ll t;
    cin >> t;
    while(t--)
    {
        str s;
        cin >> s;
        bool valid = true, r = false, g = false, b = false;
        FOR(i, 6)
        {
            if(s[i] == 'R' && !r) valid = false;
            elif(s[i] == 'G' && !g) valid = false;
            elif(s[i] == 'B' && !b) valid = false;
            elif(s[i] == 'r') r = true;
            elif(s[i] == 'g') g = true;
            elif(s[i] == 'b') b = true;
        }
        if(valid) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}