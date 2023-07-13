#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ch = char;
using str = string;

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

struct Circle {
    ll id, x, y, r, f2w, w2f;
    bool fire = true;

    bool operator<(const Circle &other) const {
        return r < other.r;
    }

    ll dist2(const Circle &other) const {
        return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y);
    }

    bool in(const Circle &other) const {
        return r < other.r && dist2(other) <= (other.r - r) * (other.r - r);
    }

    ll best_score(ll d) {
        if (d <= 0) {
            return 0;
        } elif (f2w >= 0 && w2f >= 0) {
            return (d + 1) / 2 * f2w + d / 2 * w2f;
        } elif (f2w >= 0 && w2f < 0 && f2w + w2f >= 0) {
            if (d % 2 == 0) {
                return d / 2 * f2w + (d / 2 - 1) * w2f;
            } else {
                return (d + 1) / 2 * f2w + d / 2 * w2f;
            }
        } elif (f2w < 0 && f2w + w2f >= 0) {
            return d / 2 * (f2w + w2f);
        } elif (f2w >= 0) {
            return f2w;
        } else {
            return 0;
        }
    }

    ll min_d(ll d) {
        if (d <= 0) {
            return 0;
        } elif (f2w > 0) {
            if (w2f > 0) {
                return d;
            } elif (f2w + w2f > 0) {
                return d % 2 == 1 ? d : d - 1;
            } else {
                return 1;
            }
        } elif (f2w == 0) {
            if (w2f > 0) {
                return d % 2 == 0 ? d : d - 1;
            } else {
                return 0;
            }
        } elif (f2w + w2f > 0) {
            return d % 2 == 0 ? d : d - 1;
        } else {
            return 0;
        }
    }
};

struct Node {
    Circle *circle;
    vector<Node*> children;
    ll d, cur_d, pts, min_d;
    vector<bool> anc = vector<bool>(2e3 + 1, false);

    Node(Circle *circle) : circle(circle) {}

    bool operator<(const Node &other) const {
        return circle->id < other.circle->id;
    }

    void add_child(Node *child) {
        children.pb(child);
    }

    void set_d(ll d) {
        this->d = d;
        cur_d = d;
        pts = (d + 1) / 2 * circle->f2w + d / 2 * circle->w2f;
        min_d = circle->min_d(d);
        FORE (child, children) {
            child->set_d(d + 1);
        }
    }

    void set_anc() {
        FOR (i, sz(children)) {
            children[i]->anc = anc;
            children[i]->anc[circle->id] = true;
        }
        FORE (child, children) {
            child->set_anc();
        }
    }

    ll solve() {
        ll rv = circle->best_score(d);
        FORE (child, children) {
            rv += child->solve();
        }
        return rv;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n;
    cin >> n;
    vector<Circle> circles(n + 1);
    circles[0] = {0, 0, 0, 100000, 0, 0};
    FOB (i, 1, n + 1) {
        cin >> circles[i].x >> circles[i].y >> circles[i].r >> circles[i].f2w >> circles[i].w2f;
        circles[i].id = i;
    }
    ssort(circles);
    vector<Node> nodes(n + 1, Node(&circles[0]));
    FOB (i, 1, n + 1) {
        nodes[i] = Node(&circles[i]);
    }
    FOR (i, n + 1) {
        FOB (j, i + 1, n + 1) {
            if (circles[i].in(circles[j])) {
                nodes[j].add_child(&nodes[i]);
                break;
            }
        }
    }
    nodes.back().set_d(-1);
    nodes.back().set_anc();
    ll rv = nodes.back().solve();
    ssort(nodes);
    vector<ll> ord;
    vector<bool> used(n + 1);
    while (sz(ord) <= n) {
        vector<ll> nxt;
        FOR (i, n + 1) {
            if (!used[i] && nodes[i].pts == nodes[i].circle->best_score(nodes[i].cur_d)) {
                nxt.pb(i);
            }
        }
        ll idx = 0;
        FOR (i, sz(nxt)) {
            idx = nxt[i];
            bool ok = true;
            FOR (j, sz(nxt)) {
                ll x = nxt[j];
                if (x == idx) {
                    continue;
                }
                if (nodes[x].cur_d == nodes[x].min_d && nodes[x].anc[idx]) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                break;
            }
        }
        ord.pb(idx);
        used[idx] = true;
        FOR (i, n + 1) {
            if (nodes[i].anc[idx]) {
                if (nodes[i].cur_d % 2 == 1) {
                    nodes[i].pts -= nodes[i].circle->f2w;
                } else {
                    nodes[i].pts -= nodes[i].circle->w2f;
                }
                nodes[i].cur_d--;
            }
        }
    }
    cout << rv << '\n';
    FORE (idx, ord) {
        if (idx != 0) {
            cout << idx << ' ';
        }
    }
    cout << '\n';

    return 0;
}