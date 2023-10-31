#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;
 
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
 
// #ifdef LOCAL
// #include "tester.cpp"
// #define main test_main
// extern istringstream fin;
// extern ostringstream fout;
// string test_file_name = "tests";
// #define cin fin
// #define cout fout
// #endif

ll x = 0, y = 0, idx = 0, d;
ll dx[] = {0, 1, 0, -1},
   dy[] = {1, 0, -1, 0};
map<ch, ll> dir = {{'U', 0}, {'R', 1}, {'D', 2}, {'L', 3}};
set<pair<ll, ll>> pts;
vector<ll> xs, ys, ds;

void make_move(str seq) {
    FORE (c, seq) {
        x += dx[dir[c]];
        y += dy[dir[c]];
    }
    cout << sz(seq) << ' ' << seq << endl;
    cin >> d;
    if (d == 0) {
        exit(0);
    }
    xs.pb(x);
    ys.pb(y);
    ds.pb(d);
}

void upd_mouse() {
    set<pair<ll, ll>> cur;
    if (idx == 0) {
        ll mx = xs[idx] - sqrt(ds[idx]) - 1;
        while (mx <= xs[idx] + sqrt(ds[idx]) + 1) {
            ll my/*-tien, she dgaf lil bro ._.*/ = ys[idx] - sqrt(ds[idx] - (mx - xs[idx]) * (mx - xs[idx]));
            if (ds[idx] == (mx - xs[idx]) * (mx - xs[idx]) + (my - ys[idx]) * (my - ys[idx])) {
                pts.insert({mx, my});
                my = ys[idx] + sqrt(ds[idx] - (mx - xs[idx]) * (mx - xs[idx]));
                assert(ds[idx] == (mx - xs[idx]) * (mx - xs[idx]) + (my - ys[idx]) * (my - ys[idx]));
                pts.insert({mx, my});
            }
            mx++;
        }
        idx++;
    }
    while (idx < sz(xs)) {
        FORE (p, pts) {
            auto [mx, my] = p;
            FOR (j, 4) {
                ll nx = mx + dx[j], ny = my + dy[j];
                if (ds[idx] == (nx - xs[idx]) * (nx - xs[idx]) + (ny - ys[idx]) * (ny - ys[idx])) {
                    cur.insert({nx, ny});
                }
            }
        }
        pts = cur;
        cur.clear();
        idx++;
    }
}

void add_move(str &seq, ll &cx, ll &cy, ll &mx, ll &my) {
    if (rand() & 1) {
        if (cx < mx) {
            seq += 'R';
            cx++;
        } elif (cx > mx) {
            seq += 'L';
            cx--;
        } elif (cy < my) {
            seq += 'U';
            cy++;
        } elif (cy > my) {
            seq += 'D';
            cy--;
        }
    } else {
        if (cy < my) {
            seq += 'U';
            cy++;
        } elif (cy > my) {
            seq += 'D';
            cy--;
        } elif (cx < mx) {
            seq += 'R';
            cx++;
        } elif (cx > mx) {
            seq += 'L';
            cx--;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    make_move("UU");
    make_move("RR");
    make_move("DD");
    make_move("LL");
    while (d > 0) {
        upd_mouse();
        ll i = rand() % sz(pts);
        auto it = pts.begin();
        while (i--) {
            it++;
        }
        ll mx = it->first,
            my = it->second;
        ll cx = x, cy = y;
        str seq = "";
        FOR (i, 2) {
            add_move(seq, cx, cy, mx, my);
        }
        make_move(seq);
    }

    return 0;
}