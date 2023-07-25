#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using db = double;
using cd = complex<double>;
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

struct Fractal {
    vector<cd> pts;
    vector<db> d = {0};

    Fractal(vector<cd> pts0) {
        this->pts = pts0;
        cd first = pts[0];
        cd last = pts.back();
        FOR (i, sz(pts)) {
            pts[i] -= first;
            pts[i] /= last - first;
        }
        FOB (i, 1, sz(pts)) {
            d.pb(d.back() + abs(pts[i] - pts[i - 1]));
        }
    }

    vector<cd> paste(cd &a, cd &b) {
        vector<cd> rv;
        cd diff = b - a;
        db angle = arg(diff);
        db scale = abs(diff);
        for (auto x : pts) {
            x *= scale;
            db mag = abs(x);
            x = polar(mag, arg(x) + angle);
            x += a;
            rv.pb(x);
        }
        return rv;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll t;
    cin >> t;
    while (t--) {
        ll n, depth;
        db frac;
        cin >> n;
        vector<cd> pts0(n);
        FOR (i, n) {
            db x, y;
            cin >> x >> y;
            pts0[i] = {x, y};
        }
        cin >> depth >> frac;
        if (frac == 1) {
            cout << fixed << setprecision(10) << pts0.back().real() << ' '
                << pts0.back().imag() << '\n';
            continue;
        }
        Fractal f(pts0);
        // pos, depth, idx, dist
        cd a = pts0[0], b = pts0.back();
        db cur = 0, target = abs(a - b) * frac * pow(f.d.back(), depth);
        FOR (i, depth) {
            vector<cd> pts = f.paste(a, b);
            FOR (j, sz(pts) - 1) {
                db dist = abs(pts[j] - pts[j + 1]) * pow(f.d.back(), depth - i - 1);
                if (cur + dist >= target) {
                    a = pts[j], b = pts[j + 1];
                    break;
                }
                cur += dist;
            }
        }
        cd rv = a + (b - a) * (target - cur) / abs(b - a);
        cout << fixed << setprecision(10) << rv.real() << ' ' << rv.imag() << '\n';
    }

    return 0;
}