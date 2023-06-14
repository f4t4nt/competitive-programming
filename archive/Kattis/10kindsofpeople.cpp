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
#define flip(C) reverse(C.begin(), C.end())
#define ssort(C) sort(C.begin(), C.end())
#define rsort(C) sort(C.begin(), C.end(), greater<>())

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
	vector<ll> e;
	DSU(ll N) { e = vector<ll>(N, -1); }
	ll get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
	bool same_set(ll a, ll b) { return get(a) == get(b); }
	ll size(ll x) { return -e[get(x)]; }
    ll count() {
        ll rv = 0;
        FORE (x, e) {
            if (x < 0) {
                rv++;
            }
        }
        return rv;
    }
	bool unite(ll x, ll y) {
		x = get(x), y = get(y);
		if (x == y) return false;
		if (e[x] > e[y]) swap(x, y);
		e[x] += e[y]; e[y] = x;
		return true;
	}
};

int main() {
    ll r, c;
    cin >> r >> c;
    vector<vector<bool>> grid(r, vector<bool>(c));
    FOR (i, r) {
        FOR (j, c) {
            char x;
            cin >> x;
            grid[i][j] = x == '1';
        }
    }
    DSU dsu(r * c);
    FOR (i, r) {
        FOR (j, c) {
            if (i > 0 && grid[i][j] == grid[i - 1][j]) {
                dsu.unite(i * c + j, (i - 1) * c + j);
            }
            if (j > 0 && grid[i][j] == grid[i][j - 1]) {
                dsu.unite(i * c + j, i * c + j - 1);
            }
        }
    }
    ll q;
    cin >> q;
    while (q--) {
        ll r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        r1--, c1--, r2--, c2--;
        if (grid[r1][c1] && dsu.same_set(r1 * c + c1, r2 * c + c2)) {
            cout << "decimal\n";
        } elif (!grid[r1][c1] && dsu.same_set(r1 * c + c1, r2 * c + c2)) {
            cout << "binary\n";
        } else {
            cout << "neither\n";
        }
    }
    return 0;
}