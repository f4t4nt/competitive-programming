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

ld shoelace(vector<pair<ld, ld>> v) {
    ld area = 0;
    FOR (i, sz(v)) {
        area += (v[i].first * v[(i + 1) % sz(v)].second) -
            (v[i].second * v[(i + 1) % sz(v)].first);
    }
    return abs(area) / 2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);   
    cout.tie(nullptr);

    ll n, k;
    cin >> n >> k;
    vector<pair<ld, ld>> v(n);
    FOR (i, n) {
        cin >> v[i].first >> v[i].second;
    }
    ld area = shoelace(v);

    ld expected_loss = 0;
    FOR (i, n) {
        ll j = i % n;
        ld cur_p = 1,
            cur_num = n - k,
            cur_denom = n - 2,
            cur_area = 0;
        // cur_p[d+1] = cur_p[d] * (n - d - k) / (n - d - 2)
        FOR (d, n) {
            cur_area += shoelace({v[i], v[(i + d) % n], v[(i + d + 1) % n]});
            expected_loss += cur_area * cur_p;
            cur_p *= cur_num / cur_denom;
            cur_num--, cur_denom--;
            if (cur_p == 0) {
                break;
            }
        }
    }
    expected_loss *= (ld) (k * (k - 1)) / ((ld) n * (n - 1));

    cout << fixed << setprecision(10) << area - expected_loss << '\n';

    return 0;
}