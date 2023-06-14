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

// https://open.kattis.com/problems/fancy
// https://github.com/ChrisVilches/Algorithms/blob/0d2960c6cea05fbb5a0c628c71268cb46a022824/kattis/fancy.cpp

struct Point {
    ld x, y;
    Point(ld x = 0, ld y = 0) : x(x), y(y) {}
    friend istream& operator>>(istream& in, Point& p) {
        return in >> p.x >> p.y;
    }
    friend ld operator^(const Point& p1, const Point& p2) {
        return p1.x * p2.y - p1.y * p2.x;
    }
    friend Point operator-(const Point& p1, const Point& p2) {
        return Point(p1.x - p2.x, p1.y - p2.y);
    }
};

bool in_triangle(
    Point& p,
    Point& p1,
    Point& p2,
    Point& p3,
    bool strict23 = true,
    bool strict12 = true,
    bool strict31 = true)
{
    ld s1 = (p - p1) ^ (p2 - p1);
    ld s2 = (p - p2) ^ (p3 - p2);
    ld s3 = (p - p3) ^ (p1 - p3);
    if (strict12 && s1 == 0) {
        return false;
    }
    if (strict23 && s2 == 0) {
        return false;
    }
    if (strict31 && s3 == 0) {
        return false;
    }
    return (s1 >= 0 && s2 >= 0 && s3 >= 0) || (s1 <= 0 && s2 <= 0 && s3 <= 0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m, k;
    cin >> n >> m >> k;
    vector<Point> onions(n), fences(m);
    FOR (i, n) {
        cin >> onions[i];
    }
    FOR (i, m) {
        cin >> fences[i];
    }

    vector<vector<ll>> exclude_cnt(m, vector<ll>(m, 0));
    FOR (p0, m) {
        for (ll p1 = (p0 + 1) % m; p1 != p0; p1 = (p1 + 1) % m) {
            FOR (i, n) {
                if (((onions[i] - fences[p0]) ^ (fences[p1] - fences[p0])) <= 0) {
                    exclude_cnt[p0][p1]++;
                }
            }
        }
    }

    // p0 [0, m), p1 [0, m), k_cnt [0, k], p_dp [0, m)
    // cnt of onions outside polygon p0p1...p_dp with k_cnt fences
    vector<vector<vector<vector<ll>>>> dp(m,
        vector<vector<vector<ll>>>(m,
            vector<vector<ll>>(k + 1,
                vector<ll>(m, 0))));
    
    

    ll rv = 0;
    FOR (p0, m) {
        FOB (p1, p0 + 1, m) {
            if (p0 == p1) {
                continue;
            }
            for (ll p_end = (p1 + 1) % m; p_end != p0; p_end = (p_end + 1) % m) {
                rv = min(rv, dp[p0][p1][k][p_end]);
            }
        }
    }
    cout << n - rv << '\n';

    return 0;
}