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
    tree_order_statistics_node_update
>;

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for(ll x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
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

const ld EPS = 1e-9;

ld dist(ld xi, ld yi, ld xf, ld yf) {
    return sqrt((xf - xi) * (xf - xi) + (yf - yi) * (yf - yi));
}

void move(ld xi, ld yi, ld xf, ld yf, vector<pair<str, ld>> &moves) {
    str mv = "";
    if (yf - yi > EPS) mv += "north";
    elif (yi - yf > EPS) mv += "south";
    if (xf - xi > EPS) mv += "east";
    elif (xi - xf > EPS) mv += "west";
    moves.pb({mv, dist(xi, yi, xf, yf)});
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while (true) {
        ld r, xi, yi, xf, yf;
        cin >> r;
        if (r == -1) break;
        cin >> xi >> yi >> xf >> yf;
        ld dx = abs(xf - xi), dy = abs(yf - yi);
        vector<pair<str, ld>> moves;
        if (dx == 0 || dy == 0 || dx == dy) {
            move(xi, yi, xf, yf, moves);
        } else {
            ld d = dx < dy ? dx : dy,
                xm = xi + (xf > xi ? d : -d),
                ym = yi + (yf > yi ? d : -d);
            if (dist(0, 0, xm, ym) < r) {
                move(xi, yi, xm, ym, moves);
                move(xm, ym, xf, yf, moves);
            } else {
                xm = xf - (xf > xi ? d : -d);
                ym = yf - (yf > yi ? d : -d);
                move(xi, yi, xm, ym, moves);
                move(xm, ym, xf, yf, moves);
            }
        }
        FORE (mv, moves) cout << fixed << setprecision(10) << mv.first << ' ' << mv.second << '\n';
        cout << '\n';
    }

    return 0;
}