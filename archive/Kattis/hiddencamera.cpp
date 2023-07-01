#include <bits/stdc++.h>

using namespace std;

using ll = long long;
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

ld shoelace(vector<pair<ld, ld>> &v) {
    ld area = 0;
    FOR (i, sz(v)) {
        area += (v[i].first * v[(i + 1) % sz(v)].second) -
            (v[i].second * v[(i + 1) % sz(v)].first);
    }
    return abs(area) / 2;
}

pair<ld, ld> intersection(vector<pair<ld, ld>> p) {
    ld x1 = p[0].first, y1 = p[0].second;
    ld x2 = p[1].first, y2 = p[1].second;
    ld x3 = p[2].first, y3 = p[2].second;
    ld x4 = p[3].first, y4 = p[3].second;
    ld x = ((x1 * y2 - y1 * x2) * (x3 - x4) -
        (x1 - x2) * (x3 * y4 - y3 * x4)) /
        ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));
    ld y = ((x1 * y2 - y1 * x2) * (y3 - y4) -
        (y1 - y2) * (x3 * y4 - y3 * x4)) /
        ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));
    return {x, y};
}

ll rot_quad(pair<ld, ld> &p) {
    if (p.first == 0 && p.second == 0) {
        return 0;
    } elif (p.second < p.first && p.second > -p.first) {
        return 1;
    } elif (p.second >= p.first && p.second >= -p.first) {
        return 2;
    } elif (p.second > p.first && p.second < -p.first) {
        return 3;
    } else {
        return 4;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        vector<pair<ld, ld>> v0(n);
        FOR (i, n) {
            cin >> v0[i].first >> v0[i].second;
        }
        ld area0 = shoelace(v0);
        pair<ld, ld> mid = {(v0[0].first + v0[1].first) / 2, (v0[0].second + v0[1].second) / 2};
        FORE (p, v0) {
            p.first -= mid.first;
            p.second -= mid.second;
        }
        ld theta = -atan2(v0[1].second, v0[1].first);
        FORE (p, v0) {
            ld x = p.first, y = p.second;
            p.first = x * cos(theta) - y * sin(theta);
            p.second = x * sin(theta) + y * cos(theta);
        }
        ll i = 0, i0 = -1, i1 = -1;
        while (i < n) {
            if (rot_quad(v0[i]) != 1 && rot_quad(v0[(i - 1 + n) % n]) == 1) {
                assert(i0 == -1);
                i0 = i;
            }
            if (rot_quad(v0[i]) != 3 && rot_quad(v0[(i + 1) % n]) == 3) {
                assert(i1 == -1);
                i1 = i;
            }
            i++;
        }
        assert(i0 != -1 && i1 != -1);
        pair<ld, ld> p0 = intersection({v0[(i0 - 1 + n) % n], v0[i0], {0,0}, {1,1}}),
            p1 = intersection({v0[i1], v0[(i1 + 1) % n], {0,0}, {-1,1}});
        vector<pair<ld, ld>> v1 = {{0, 0}, p0};
        i = 0;
        while (i < n) {
            if (rot_quad(v0[i]) == 2) {
                v1.push_back(v0[i]);
            }
            i++;
        }
        v1.push_back(p1);
        ld area1 = shoelace(v1), rv = area1 / area0;
        cout << fixed << setprecision(10) << rv << '\n';
    }

    return 0;
}