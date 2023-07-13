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

struct Location {
    ll lvl, x,  y, d;
};

void reduce(ll &x, ll &hsz, ll &xtra) {
    if (x < -1) {
        xtra += -1 - x;
        x = -1;
    } elif (x > hsz - 1) {
        xtra += x - hsz + 1;
        x = hsz - 1;
    }
}

vector<Location*> get_path(ll x, ll y, ll lvl) {
    vector<Location*> rv;
    ll d = 0;
    if (lvl == 1) {
        if (x == 0 && y == 0) {
            d = 1;
            y = -1;
        }
        rv.pb(new Location{lvl, x, y, d});
        return rv;
    }
    ll hsz = 1LL << lvl, quad = (x >= hsz / 2) + (y >= hsz / 2) * 2;
    ll nx, ny;
    if (quad == 0) {
        nx = hsz / 2 - y - 2;
        ny = x;
    } elif (quad == 1) {
        nx = y;
        ny = hsz - x - 2;
    } elif (quad == 2) {
        nx = x;
        ny = y - hsz / 2;
    } else {
        nx = x - hsz / 2;
        ny = y - hsz / 2;
    }
    rv = get_path(nx, ny, lvl - 1);
    Location* l = rv[0];
    d = l->d, nx = l->x, ny = l->y;
    if (nx > -1 && nx < hsz / 2 - 1 && ny > -1 && ny < hsz / 2 - 1) {
        if (ny <= hsz / 4  - 1) {
            d += abs(hsz / 4 - nx - 1);
            nx = hsz / 4 - 1;
            rv.insert(rv.begin(), new Location{lvl, nx, ny, d});
            d += ny + 1;
            ny = -1;
        } else {
            d += hsz / 2 - ny - 1;
            ny = hsz / 2 - 1;        
        }
    }
    rv.insert(rv.begin(), new Location{lvl, nx, ny, d});
    FORE (loc, rv) {
        if (quad == 0) {
            x = loc->y;
            y = hsz / 2 - loc->x - 2;
        } elif (quad == 1) {
            x = hsz - loc->y - 2;
            y = loc->x;
        } elif (quad == 2) {
            x = loc->x;
            y = loc->y + hsz / 2;
        } else {
            x = loc->x + hsz / 2;
            y = loc->y + hsz / 2;
        }
        loc->x = x;
        loc->y = y;
    }
    return rv;
}

vector<Location*> extend_to_exterior(vector<Location*> p) {
    ll nx = p[0]->x, ny = p[0]->y, d = p[0]->d, lvl = p[0]->lvl, hsz = 1LL << lvl;
    if (nx > -1 && nx < hsz - 1 && ny > -1 && ny < hsz - 1) {
        if (ny <= hsz / 2  - 1) {
            d += abs(hsz / 2 - nx - 1);
            nx = hsz / 2 - 1;
            p.insert(p.begin(), new Location{lvl + 1, nx, ny, d});
            d += ny + 1;
            ny = -1;
        } else {
            d += hsz - ny - 1;
            ny = hsz - 1;
        }
    }
    p.insert(p.begin(), new Location{lvl + 1, nx, ny, d});
    return p;
}

ll get_edge(Location* loc, ll hsz) {
    if (loc->y <= -1) {
        return 0;
    } elif (loc->x <= -1) {
        return 1;
    } elif (loc->y >= hsz - 1) {
        return 2;
    } else {
        return 3;
    }
}

ll exterior_dist(Location* loc1, Location* loc2, ll hsz) {
    ll e1 = get_edge(loc1, hsz), e2 = get_edge(loc2, hsz);
    if (e1 == 0) {
        if (e2 == 0) {
            return abs(loc1->x - loc2->x);
        } elif (e2 == 1) {
            return loc1->x + loc2->y + 2;
        } elif (e2 == 2) {
            return min(loc1->x + loc2->x + 2, 2 * hsz - loc1->x - loc2->x - 2) + hsz;
        } else {
            return hsz - loc1->x + loc2->y;
        }
    } elif (e1 == 1) {
        if (e2 == 0) {
            return loc1->y + loc2->x + 2;
        } elif (e2 == 1) {
            return abs(loc1->y - loc2->y);
        } elif (e2 == 2) {
            return hsz - loc1->y + loc2->x;
        } else {
            return min(loc1->y + loc2->y + 2, 2 * hsz - loc1->y - loc2->y - 2) + hsz;
        }
    } elif (e1 == 2) {
        if (e2 == 0) {
            return min(loc1->x + loc2->x + 2, 2 * hsz - loc1->x - loc2->x - 2) + hsz;
        } elif (e2 == 1) {
            return loc1->x + hsz - loc2->y;
        } elif (e2 == 2) {
            return abs(loc1->x - loc2->x);
        } else {
            return 2 * hsz - loc1->x - loc2->y - 2;
        }
    } else {
        if (e2 == 0) {
            return loc1->y + hsz - loc2->x;
        } elif (e2 == 1) {
            return min(loc1->y + loc2->y + 2, 2 * hsz - loc1->y - loc2->y - 2) + hsz;
        } elif (e2 == 2) {
            return 2 * hsz - loc1->y - loc2->x - 2;
        } else {
            return abs(loc1->y - loc2->y);
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll t;
    cin >> t;
    while (t--) {
        ll x1, y1, x2, y2, hsz, xtra = 0, lvl, rv = 0;
        cin >> lvl >> x1 >> y1 >> x2 >> y2;
        hsz = 1LL << lvl;
        if ((x1 <= -1 && x2 <= -1) ||
            (x1 >= hsz - 1 && x2 >= hsz - 1) ||
            (y1 <= -1 && y2 <= -1) ||
            (y1 >= hsz - 1 && y2 >= hsz - 1))
        {
            rv = abs(x1 - x2) + abs(y1 - y2);
        } elif (x1 != x2 || y1 != y2) {
            reduce(x1, hsz, xtra);
            reduce(x2, hsz, xtra);
            reduce(y1, hsz, xtra);
            reduce(y2, hsz, xtra);
            auto p1 = get_path(x1, y1, lvl);
            p1 = extend_to_exterior(p1);
            auto p2 = get_path(x2, y2, lvl);
            p2 = extend_to_exterior(p2);
            if (p1[0]->x != p2[0]->x || p1[0]->y != p2[0]->y) {
                rv = p1[0]->d + p2[0]->d;
                rv += exterior_dist(p1[0], p2[0], hsz);
                rv += xtra;
            } else {
                ll i = 0;
                while (i < sz(p1) - 1 && i < sz(p2) - 1 && p1[i]->x == p2[i]->x && p1[i]->y == p2[i]->y) {
                    i++;
                }
                rv = p1[i]->d + p2[i]->d;
                rv += abs(p1[i]->x - p2[i]->x) + abs(p1[i]->y - p2[i]->y);
                rv += xtra;
            }
        }
        cout << rv << '\n';
    }

    return 0;
}