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
 
#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

const ld EPS = 1e-3;

struct Point {
    ld x, y;
    Point operator+(Point o) {
        return {x + o.x, y + o.y};
    }
    Point operator-(Point o) {
        return {x - o.x, y - o.y};
    }
    Point operator*(ld k) {
        return {x * k, y * k};
    }
    Point operator/(ld k) {
        return {x / k, y / k};
    }
    ld abs2() {
        return x * x + y * y;
    }
    ld abs_() {
        return sqrt(abs2());
    }
    bool operator==(Point o) {
        return abs(x - o.x) < EPS && abs(y - o.y) < EPS;
    }
    bool operator!=(Point o) {
        return abs(x - o.x) > EPS || abs(y - o.y) > EPS;
    }
};

struct Circle {
    Point c;
    ld r;
    ll id;
    Circle(Point c, ld r, ll id) : c(c), r(r), id(id) {}
    Circle() {}
    bool has(Point &p) {
        return (p - c).abs_() <= r + EPS;
    }
    vector<Point> operator&(Circle &o) {
        if ((c - o.c).abs_() > r + o.r + EPS || (c - o.c).abs_() < abs(r - o.r) - EPS) {
            return {};
        }
        if ((c - o.c).abs_() < EPS && abs(r - o.r) < EPS) {
            return {{c.x + r, c.y}};
        }
        Point sum = o.c + c, diff = o.c - c, perp = {diff.y, -diff.x};
        ld csu = 0.5,
            cdi = (r * r - o.r * o.r) / (2 * diff.abs2()),
            cpe = 0.5 * sqrt(max((ld) 0, 2 * (r * r + o.r * o.r) / (diff.abs2())
                - (r * r - o.r * o.r) * (r * r - o.r * o.r) / (diff.abs2() * diff.abs2()) - 1));
        vector<Point> rv = {sum * csu + diff * cdi + perp * cpe, sum * csu + diff * cdi - perp * cpe};
        return rv;
    }
};

bool is_adj(Point &p0, Point &p1, vector<Circle> &circles) {
    ll cur_circ = -1;
    vector<bool> vis(sz(circles));
    FORE (c, circles) {
        if (c.has(p0)) {
            cur_circ = c.id;
            vis[cur_circ] = true;
            break;
        }
    }
    if (cur_circ == -1) return false;
    Point cur = p0;
    ld lo = 0, hi = 1;
    while (lo < 1 - 1e-12) {
        hi = 1;
        while (hi - lo > 1e-12) {
            ld mid = (lo + hi) / 2;
            Point nxt = p0 + (p1 - p0) * mid;
            if (circles[cur_circ].has(nxt)) {
                cur = nxt;
                lo = mid;
            } else {
                hi = mid;
            }
        }
        if (lo >= 1 - 1e-12) break;
        bool ok = false;
        FORE (c, circles) {
            if (c.has(cur) && !vis[c.id]) {
                cur_circ = c.id;
                vis[cur_circ] = true;
                ok = true;
                break;
            }
        }
        if (!ok) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    Point p0, p1;
    cin >> p0.x >> p0.y >> p1.x >> p1.y;
    ll n;
    cin >> n;
    vector<Circle> circles(n);
    FOR (i, n) {
        cin >> circles[i].c.x >> circles[i].c.y >> circles[i].r;
        circles[i].id = i;
    }
    // direct?
    ld split = 1e7;
    vector<Point> ps = {p0};
    Point delta = (p1 - p0) / split;
    FOR (i, split) {
        ps.pb(ps.back() + delta);
    }
    vector<Point> points = {p0, p1};
    FOR (i, n) {
        FOB (j, i + 1, n) {
            vector<Point> ps = circles[i] & circles[j];
            points.insert(points.end(), all(ps));
        }
    }
    vector<vector<pair<ll, ld>>> graph(sz(points));
    FOR (i, sz(points)) {
        FOB (j, i + 1, sz(points)) {
            if (is_adj(points[i], points[j], circles)) {
                graph[i].pb({j, (points[i] - points[j]).abs_()});
                graph[j].pb({i, (points[i] - points[j]).abs_()});
            }
        }
    }
    vector<ld> dist(sz(points), 1e18);
    dist[0] = 0;
    std::priority_queue<pair<ld, ll>, vector<pair<ld, ll>>, greater<>> pq;
    pq.push({0, 0});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        FORE (e, graph[u]) {
            if (dist[u] + e.second < dist[e.first]) {
                dist[e.first] = dist[u] + e.second;
                pq.push({dist[e.first], e.first});
            }
        }
    }
    if (dist[1] == 1e18) cout << "impossible\n";
    else cout << fixed << setprecision(10) << dist[1] << '\n';

    return 0;
}