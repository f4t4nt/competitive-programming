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

struct DSU {
    ll cnt;
	vector<ll> e;
	DSU(ll n) { e = vector<ll>(n, -1); cnt = n; }
    void reset() { e = vector<ll>(sz(e), -1); cnt = sz(e); }
	ll get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
	bool same_set(ll a, ll b) { return get(a) == get(b); }
	ll size(ll x) { return -e[get(x)]; }
    ll count() { return cnt; }
	bool unite(ll x, ll y) {
		x = get(x), y = get(y);
		if (x == y) return false;
		if (e[x] > e[y]) swap(x, y);
		e[x] += e[y]; e[y] = x;
        cnt--;
		return true;
	}
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m, cells = 0;
    cin >> n >> m;
    vector<vector<ll>> grid(n, vector<ll>(m));
    FOR (i, n) {
        FOR (j, m) {
            ch c;
            cin >> c;
            if (c == '.') {
                grid[i][j] = cells++;
            } else {
                grid[i][j] = -1;
            }
        }
    }
    
    DSU dsu(cells);
    FOR (i, n) {
        FOR (j, m) {
            if (grid[i][j] != -1) {
                if (i > 0 && grid[i - 1][j] != -1) {
                    dsu.unite(grid[i][j], grid[i - 1][j]);
                }
                if (j > 0 && grid[i][j - 1] != -1) {
                    dsu.unite(grid[i][j], grid[i][j - 1]);
                }
            }
        }
    }

    cout << dsu.count() << '\n';

    return 0;
}