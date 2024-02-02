#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef complex<long double> cd;
typedef long double ld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

using indexed_set = tree<
    pair<ll, ll>,
    null_type,
    less<pair<ll, ll>>,
    rb_tree_tag,
    tree_order_statistics_node_update>;

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)
#define FOB(x, b, e) for (auto x = b; x < e; x++)
#define FORE(x, C) for (auto &x : C)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

typedef pair<ll, ll> pll;

#define x first
#define y second

vector<pair<ll, ll>> convex_hull(vector<pair<ll, ll>> pts) {
    if (sz(pts) <= 1) return pts;
    ssort(pts);
    vector<pair<ll, ll>> lo, hi;
    FORE (p, pts) {
        while (sz(lo) >= 2) {
            auto &p1 = lo[sz(lo) - 2], &p2 = lo[sz(lo) - 1];
            if ((p2.y - p1.y) * (p.x - p2.x) >= (p.y - p2.y) * (p2.x - p1.x)) {
                lo.pop_back();
            } else break;
        }
        lo.pb(p);
    }
    for (auto it = pts.rbegin(); it != pts.rend(); it++) {
        auto &p = *it;
        while (sz(hi) >= 2) {
            auto &p1 = hi[sz(hi) - 2], &p2 = hi[sz(hi) - 1];
            if ((p2.y - p1.y) * (p.x - p2.x) >= (p.y - p2.y) * (p2.x - p1.x)) {
                hi.pop_back();
            } else break;
        }
        hi.pb(p);
    }
    lo.pop_back(), hi.pop_back();
    lo.insert(lo.end(), hi.begin(), hi.end());
    return lo;
}

vector<pll> boy;
vector<pll> girl;
string s;
int n;
ll x, y;
ld ans;

ld dist(pll p1, pll p2)
{
    ll total=(p1.first-p2.first)*(p1.first-p2.first)+(p1.second-p2.second)*(p1.second-p2.second);
    return sqrt((long double) total);
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    boy.clear();
    girl.clear();
    ans = 0;

    cin >> n >> s;
    for (int i=0; i<s.length(); i++)
    {
        cin >> x >> y;
        if (s[i]=='B')
            boy.pb(pll (x, y));
        else
            girl.pb(pll (x, y));
    }
    // boy=convex_hull(boy);
    // girl=convex_hull(girl);
    ll a=boy.size()/2;
    ll b=girl.size()/2;
    for (int i=0; i<a; i++)
    {
        ans+=dist(boy[i], boy[i+a]);
    }
    for (int i=0; i<b; i++)
    {
        ans+=dist(girl[i], girl[i+b]);
    }
    cout << fixed << setprecision(10) << ans << endl;

    return 0;
}