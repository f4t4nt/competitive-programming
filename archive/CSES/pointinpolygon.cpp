#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

using indexed_set = tree<
    ll,
    null_type,
    less<ll>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;

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

struct Point {
    ll x, y;
};
 
bool on_segment(Point &p, Point &q, Point &r) {
    return (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y));
}
 
ll orientation(Point &p, Point &q, Point &r) {
    ll val = (q.y - p.y) * (r.x - q.x) -
        (q.x - p.x) * (r.y - q.y);
    if (val == 0) {
        return 0;
    }
    return (val > 0) ? 1 : 2;
}
 
bool intersect(Point &p1, Point &q1, Point &p2, Point &q2) {
    ll o1 = orientation(p1, q1, p2);
    ll o2 = orientation(p1, q1, q2);
    ll o3 = orientation(p2, q2, p1);
    ll o4 = orientation(p2, q2, q1);
    if (o1 != o2 && o3 != o4) {
        return true;
    }
    if (o1 == 0 && on_segment(p1, p2, q1)) {
        return true;
    }
    if (o2 == 0 && on_segment(p1, q2, q1)) {
        return true;
    }
    if (o3 == 0 && on_segment(p2, p1, q2)) {
        return true;
    }
    if (o4 == 0 && on_segment(p2, q1, q2)) {
        return true;
    }
    return false;
}

ll shoelace(vector<Point> v) {
    ll n = sz(v);
    ll area = 0;
    FOR (i, n) {
        area += v[i].x * v[(i + 1) % n].y;
        area -= v[i].y * v[(i + 1) % n].x;
    }
    return abs(area);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, t;
    cin >> n >> t;
    vector<Point> v(n);
    FORE (p, v) {
        cin >> p.x >> p.y;
    }
    while (t--) {
        Point p, inf;
        cin >> p.x >> p.y;
        bool on_edge = false;
        FOR (i, n) {
            if (shoelace({v[i], v[(i + 1) % n], p}) == 0 &&
                on_segment(v[i], p, v[(i + 1) % n]))
            {
                on_edge = true;
                break;
            }
        }
        if (on_edge) {
            cout << "BOUNDARY\n";
            continue;
        }
        inf = {1234567890, p.y + 1};
        ll cnt = 0;
        FOR (i, n) {
            if (intersect(p, inf, v[i], v[(i + 1) % n])) {
                cnt++;
            }
        }
        cout << (cnt % 2 ? "INSIDE" : "OUTSIDE") << '\n';
    }

    return 0;
}