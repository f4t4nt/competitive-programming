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
using mplll = map<pll, ll>;
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

// #ifdef LOCAL
// #include "tester.cpp"
// #define main test_main
// extern istringstream fin;
// extern ostringstream fout;
// string test_file_name = "tests";
// #define cin fin
// #define cout fout
// #endif

// https://codeforces.com/contest/1634/problem/D

int main()
{
    ll T;
    cin >> T;
    while(T--)
    {
        ll N, maxv = -1, maxi = -1, minv = -1, mini = -1, midv0, midv1, midv2, midv3, midi = -1, tmpv;
        cin >> N;

        cout << "? 1 2 3\n";
        cout.flush();
        cin >> midv0;
        cout << "? 1 2 4\n";
        cout.flush();
        cin >> midv1;
        cout << "? 1 3 4\n";
        cout.flush();
        cin >> midv2;
        cout << "? 2 3 4\n";
        cout.flush();
        cin >> midv3;
        if(midv0 == midv1 && midv0 >= midv2 && midv0 >= midv3) midi = 2;
        elif(midv0 == midv2 && midv0 >= midv1 && midv0 >= midv3) midi = 1;
        elif(midv0 == midv3 && midv0 >= midv1 && midv0 >= midv2) midi = 3;
        elif(midv1 == midv2 && midv1 >= midv0 && midv1 >= midv3) midi = 1;
        elif(midv1 == midv3 && midv1 >= midv0 && midv1 >= midv2) midi = 2;
        elif(midv2 == midv3 && midv2 >= midv0 && midv2 >= midv1) midi = 1;

        FOB(i, 1, N)
        {
            if(midi == i) continue;
            if((midi == 1 && i == 2) || (midi == 2 && i == 1)) tmpv = midv0;
            elif((midi == 1 && i == 3) || (midi == 3 && i == 1)) tmpv = midv1;
            elif((midi == 2 && i == 3) || (midi == 3 && i == 2)) tmpv = midv2;
            else
            {
                cout << "? 1 " << midi + 1 << ' ' << i + 1 << '\n';
                cout.flush();
                cin >> tmpv;
            }
            if(tmpv > maxv)
            {
                maxi = i;
                maxv = tmpv;
            }
        }

        FOR(i, N)
        {
            if(maxi == i || midi == i) continue;
            if(i == 0) tmpv = maxv;
            elif(midi + maxi + i == 6 && min(midi, min(maxi, i)) == 1 && max(midi, max(maxi, i)) == 3) tmpv = midv3;
            else
            {
                cout << "? " << midi + 1 << ' ' << maxi + 1 << ' ' << i + 1 << '\n';
                cout.flush();
                cin >> tmpv;
            }
            if (tmpv > minv)
            {
                mini = i;
                minv = tmpv;
            }
        }

        cout << "! " << maxi + 1 << ' ' << mini + 1 << '\n';
    }
    return 0;
}