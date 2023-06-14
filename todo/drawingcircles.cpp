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

// https://open.kattis.com/problems/drawingcircles1

constexpr ld ADD_CNT = 180;

struct Circle {
    ld x, y, r;
};

ld dist2(ld x1, ld y1, ld x2, ld y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

bool valid(Circle &c, vector<Circle> &circles) {
    FORE (c2, circles) {
        if (dist2(c.x, c.y, c2.x, c2.y) < (c.r + c2.r) * (c.r + c2.r)) {
            return false;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ld w, h;
    cin >> w >> h;
    ll n;
    cin >> n;
    vector<Circle> circles(n);
    FOR (i, n) {
        cin >> circles[i].x >> circles[i].y >> circles[i].r;
    }

    ld lo = 0, hi = 76.546145369402169 * 2;
    while (abs(lo - hi) > 1e-9) {
        ld mid = (lo + hi) / 2;
        set<pair<ld, ld>> points;
        FOR (i, n) {
            Circle &ci = circles[i];
            ld ri = ci.r + mid;
            FOB (j, i + 1, n) {
                Circle &cj = circles[j];
                ld rj = cj.r + mid;
                if (ci.x == cj.x && ci.y == cj.y && ri == rj) {
                    continue;
                }   
                ld d2 = dist2(ci.x, ci.y, cj.x, cj.y),
                    d = sqrt(d2);
                if (d > ri + rj) {
                    continue;
                }
                if (d + ri < rj || d + rj < ri) {
                    continue;
                }
                ld xm = (ci.x + cj.x) / 2,
                    ym = (ci.y + cj.y) / 2;
                ld xd = ci.x - cj.x,
                    yd = ci.y - cj.y;
                ld xc = xm + xd * (ri * ri - rj * rj) / (2 * d2),
                    yc = ym + yd * (ri * ri - rj * rj) / (2 * d2);
                ld c = 0.5 * sqrt(2 * (ri * ri + rj * rj) / d2 - (ri * ri - rj * rj) * (ri * ri - rj * rj) / d2 / d2 - 1);
                ld x1 = xc + c * yd,
                    y1 = yc - c * xd,
                    x2 = xc - c * yd,
                    y2 = yc + c * xd;
                points.insert({x1, y1});
                points.insert({x2, y2});
            }
            if (ci.x - ri <= mid) {
                ld d = ci.x - mid;
                ld y1 = ci.y + sqrt(ri * ri - d * d),
                    y2 = ci.y - sqrt(ri * ri - d * d);
                points.insert({mid, y1});
                points.insert({mid, y2});
            }
            if (ci.x + ri >= w - mid) {
                ld d = w - mid - ci.x;
                ld y1 = ci.y + sqrt(ri * ri - d * d),
                    y2 = ci.y - sqrt(ri * ri - d * d);
                points.insert({w - mid, y1});
                points.insert({w - mid, y2});
            }
            if (ci.y - ri <= mid) {
                ld d = ci.y - mid;
                ld x1 = ci.x + sqrt(ri * ri - d * d),
                    x2 = ci.x - sqrt(ri * ri - d * d);
                points.insert({x1, mid});
                points.insert({x2, mid});
            }
            if (ci.y + ri >= h - mid) {
                ld d = h - mid - ci.y;
                ld x1 = ci.x + sqrt(ri * ri - d * d),
                    x2 = ci.x - sqrt(ri * ri - d * d);
                points.insert({x1, h - mid});
                points.insert({x2, h - mid});
            }
            FOR (a, ADD_CNT) {
                points.insert({ci.x + ri * cos(2 * M_PI * a / ADD_CNT),
                    ci.y + ri * sin(2 * M_PI * a / ADD_CNT)});
            }
        }
        points.insert({mid, mid});
        points.insert({w - mid, mid});
        points.insert({mid, h - mid});
        points.insert({w - mid, h - mid});
        bool ok = false;
        FORE (p, points) {
            Circle c = {p.first, p.second, mid};
            if (c.x - c.r >= 0 && c.x + c.r <= w &&
                c.y - c.r >= 0 && c.y + c.r <= h &&
                valid(c, circles))
            {
                ok = true;
                break;
            }
        }
        if (ok) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    cout << fixed << setprecision(18) << lo << '\n';

    return 0;
}