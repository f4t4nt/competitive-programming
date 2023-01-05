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

using vi = vector<int>;
using vvi = vector<vi>;
using ll = long long;
using ull = unsigned long long;
using vl = vector<ll>;
using vvl = vector<vl>;
using vvvl = vector<vvl>;
using vvvvl = vector<vvvl>;
using pll = pair<ll, ll>;
using vpll = vector<pll>;
using vvpll = vector<vpll>;
using plvpll = pair<ll, vpll>;
using plvl = pair<ll, vl>;
using vplvl = vector<plvl>;
using sl = set<ll>;
using spll = set<pll>;
using vsl = vector<sl>;
using ssl = set<sl>;
using plsl = pair<ll, sl>;
using vplsl = vector<plsl>;
using plspll = pair<ll, spll>;
using msl = multiset<ll>;
using mspll = multiset<pll>;
using vb = vector<bool>;
using vvb = vector<vb>;
using plvb = pair<ll, vb>;
using mll = map<ll, ll>;
using mlll = map<ll, mll>;
using mlvl = map<ll, vl>;
using mlpll = map<ll, pll>;
using mlvpll = map<ll, vpll>;
using mlsl = map<ll, sl>;
using mpllb = map<pll, bool>;
using vmll = vector<mll>;
using ql = queue<ll>;
using qpll = queue<pll>;
using fl = long double;
using vf = vector<fl>;
using vvf = vector<vf>;
using str = string;
using vstr = vector<str>;
using mstrl = map<str, ll>;
using mcl = map<char, ll>;

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

// https://codeforces.com/contest/1621/problem/B

struct Segment
{
    ll L;
    ll R;
    ll C;
};

int main()
{
    ll T;
    cin >> T;
    while(T--)
    {
        ll N;
        cin >> N;
        vector<Segment> A(N);
        FOR(i, N)
        { cin >> A[i].L >> A[i].R >> A[i].C; }
        Segment L = A[0], R = A[0], X = A[0];
        cout << L.C << '\n';
        FOB(i, 1, N)
        {
            if(A[i].L < L.L)
            { L = A[i]; }
            elif(A[i].L == L.L && A[i].C < L.C)
            { L = A[i]; }
            if(A[i].R > R.R)
            { R = A[i]; }
            elif(A[i].R == R.R && A[i].C < R.C)
            { R = A[i]; }
            if(A[i].R - A[i].L > X.R - X.L)
            { X = A[i]; }
            elif(A[i].R - A[i].L >= X.R - X.L && A[i].C < X.C)
            { X = A[i]; }
            if(X.R - X.L > R.R - L.L)
            { cout << X.C << '\n'; }
            elif(X.R - X.L == R.R - L.L)
            { cout << min(X.C, L.C + R.C) << '\n'; }
            else
            { cout << L.C + R.C << '\n'; }
        }
    }
    return 0;
}