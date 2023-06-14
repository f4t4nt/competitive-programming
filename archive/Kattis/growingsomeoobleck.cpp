#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using cd = complex<double>;
using ch = char;
using str = string;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define mp make_pair
#define mt make_tuple
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for(ll x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
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

struct Oobleck {
    bool active = false;
    ld t = 0, x, y, r, s;

    Oobleck() : x(0), y(0), r(0), s(0) {}

    Oobleck(ld x, ld y, ld r, ld s, ld t) : x(x), y(y), r(r), s(s), t(t) {}

    ld time_to_reach(Oobleck &o) {
        ld r0 = r - s * t, or0 = o.r - o.s * o.t;
        ld dx = x - o.x, dy = y - o.y;
        ld d = sqrt(dx * dx + dy * dy);
        ld dr = r0 + or0;
        ld rv = (d - dr) / (s + o.s);
        return rv;
    }
};

Oobleck merge(set<Oobleck*> ooblecks, ld t) {
    ld nx = 0, ny = 0, nr = 0, ns = 0;
    FORE (o, ooblecks) {
        o->r = max(o->r, o->r + o->s * (t - o->t));
        o->t = t;
        nr += (o->r * o->r);
        ns = max(ns, o->s);
        nx += o->x;
        ny += o->y;
        o->active = false;
    }
    nr = sqrt(nr);
    nx /= sz(ooblecks);
    ny /= sz(ooblecks);
    return Oobleck(nx, ny, nr, ns, t);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    ll idx = n;
    vector<Oobleck> ooblecks(n * (n + 1) / 2);
    set<Oobleck*> active;
    priority_queue<tuple<ld, Oobleck*, Oobleck*>,
        vector<tuple<ld, Oobleck*, Oobleck*>>,
        greater<>> pq;
    while (n--) {
        Oobleck &o = ooblecks[n];
        cin >> o.x >> o.y >> o.r >> o.s;
        FORE (a, active) {
            pq.push(mt(o.time_to_reach(*a), &o, a));
        }
        o.active = true;
        active.insert(&o);
    }

    ld cur_t = 0;
    while (!pq.empty()) {
        ld t;
        set<Oobleck*> to_merge;
        Oobleck *a, *b;
        while (!pq.empty()) {
            tie(t, a, b) = pq.top();
            if (a->active && b->active) {
                break;
            }
            pq.pop();
        }
        if (a->active && b->active) {
            to_merge.insert(a);
            to_merge.insert(b);
            if (t < cur_t) {
                while (!pq.empty()) {
                    tie(t, a, b) = pq.top();
                    if (t < cur_t) {
                        if (a->active && b->active) {
                            to_merge.insert(a);
                            to_merge.insert(b);
                        }
                        pq.pop();
                    } else {
                        break;
                    }
                }
            } else {
                cur_t = t;
            }
            ooblecks[idx] = merge(to_merge, cur_t);
            FORE (o, to_merge) {
                active.erase(o);
            }
            FORE (o, active) {
                pq.push(mt(o->time_to_reach(ooblecks[idx]), o, &ooblecks[idx]));
            }
            ooblecks[idx].active = true;
            active.insert(&ooblecks[idx]);
            idx++;
        }
    }

    Oobleck rv = ooblecks[idx - 1];
    cout << fixed << setprecision(10) << rv.x << ' ' << rv.y << '\n' << rv.r << '\n';

    return 0;
}