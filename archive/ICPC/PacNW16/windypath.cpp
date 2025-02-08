#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef complex<long double> cd;
typedef long double ld;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

using indexed_set = tree<
    ll,
    null_type,
    less<ll>,
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
#define x first
#define y second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FOR1(x, e) for (ll x = 1; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

ld angle(pld p0, pld p1, pld p2) { // angle between vec p0p1 and p0p2
    pld w = {p1.x - p0.x, p1.y - p0.y},
        v = {p2.x - p0.x, p2.y - p0.y};
    ld res = atan2(
        w.y * v.x - w.x * v.y,
        w.x * v.x + w.y * v.y
    );
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n; cin >> n;
    vector<pld> pts(n);
    pld mn = { 1e18, 1e18 };
    map<pld, ll> id;
    for (pld &p : pts) {
        cin >> p.x >> p.y;
        id[p] = sz(id);
        mn = min(mn, p);
    }
    set<pld> rem(all(pts));
    vector<ll> ord = { id[mn] };
    rem.erase(mn);
    str s; cin >> s;
    for (ch c : s) {
        pld cur = pts[ord.back()],
            avg = { 0, 0 },
            nxt = { 1e18, 1e18 };
        ld best = 0;
        for (pld pt : rem) {
            avg.x += pt.x;
            avg.y += pt.y;
        }
        avg.x /= sz(rem);
        avg.y /= sz(rem);
        for (pld pt : rem) {
            ld deg = angle(cur, avg, pt);
            cerr << fixed << setprecision(10) << pt.x << ' ' << pt.y << ": " << deg << endl;
            if (c == 'L' && deg > best) {
                best = deg;
                nxt = pt;
            } elif (c == 'R' && deg < best) {
                best = deg;
                nxt = pt;
            }
        }
        cerr << endl;
        ord.pb(id[nxt]);
        rem.erase(nxt);
    }
    ord.pb(id[*rem.begin()]);
    for (ll i : ord) cout << i + 1 << ' ';
    cout << '\n';

    return 0;
}