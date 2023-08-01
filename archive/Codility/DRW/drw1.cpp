#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using db = double;
using cd = complex<double>;
using ld = long double;
using ch = char;
using str = string;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

using indexed_set = tree<
    ll,
    null_type,
    less<ll>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;

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

int solution(vector<int> &a, vector<int> &b, int n) {
    FORE (v, a) v--;
    FORE (v, b) v--;
    vector<set<int>> adj(n);
    FOR (i, sz(a)) {
        adj[a[i]].insert(b[i]);
        adj[b[i]].insert(a[i]);
    }
    ll rv = 0;
    FOR (i, n) {
        FORE (j, adj[i]) {
            rv = max(rv, sz(adj[i]) + sz(adj[j]) - 1);
        }
    }
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    vector<int> a(m), b(m);
    FOR (i, m) cin >> a[i];
    FOR (i, m) cin >> b[i];
    cout << solution(a, b, n) << '\n';

    return 0;
}