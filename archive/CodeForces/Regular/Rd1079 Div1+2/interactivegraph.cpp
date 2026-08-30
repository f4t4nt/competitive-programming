#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef long double ld;
typedef complex<ld> cd;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

template<typename T>
using indexed_set = tree<
    T,
    null_type,
    less<T>,
    rb_tree_tag,
    tree_order_statistics_node_update>;
// s.order_of_key(x) -> number of elements < x
// s.find_by_order(x) -> iterator to the x-th element (0-indexed)

#pragma GCC target("popcnt,lzcnt")
// __builtin_popcount(x) -> number of set bits
// __builtin_clz(x) -> number of leading zeros
// for ll, use __builtin_popcountll, __builtin_clzll

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
#define f first
#define s second

// #ifdef LOCAL
// #include "tester.cpp"
// #define main test_main
// extern istringstream fin;
// extern ostringstream fout;
// string test_file_name = "tests";
// #define cin fin
// #define cout fout
// #endif

ll n, S[35];
bool has_edge[35][35];
vector<pll> edges;

vector<ll> ask(ll k) {
    cout << "? " << k << endl;
    ll q; cin >> q;
    vector<ll> path(q);
    for (ll &x : path) cin >> x;
    return path;
}

bool is_prefix(vector<ll> &path, vector<ll> &pref) {
    if (sz(path) < sz(pref)) return false;
    for (ll i = 0; i < sz(pref); i++) {
        if (path[i] != pref[i]) return false;
    }
    return true;
}

void solve_vertex(ll v, ll start, vector<ll> &pref) {
    if (S[v] != -1) return;

    ll pos = start + 1, total = 1;

    while (true) {
        vector<ll> p = ask(pos);

        if (sz(p) == 0) break;
        if (!is_prefix(p, pref)) break;
        ll to = p[sz(pref)];

        if (!has_edge[v][to]) {
            has_edge[v][to] = true;
            edges.pb({v, to});
        }

        if (S[to] == -1) {
            vector<ll> child_pref = pref;
            child_pref.pb(to);
            solve_vertex(to, pos, child_pref);
        }

        total += S[to];
        pos += S[to];
    }

    S[v] = total;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        cin >> n;

        edges.clear();
        memset(S, -1, sizeof(S));
        memset(has_edge, false, sizeof(has_edge));

        ll start_pos = 1;
        for (ll v = 1; v <= n; v++) {
            if (S[v] == -1) {
                vector<ll> pref;
                pref.pb(v);
                solve_vertex(v, start_pos, pref);
            }
            start_pos += S[v];
        }

        cout << "! " << sz(edges) << '\n';
        for (auto& [u, v] : edges) cout << u << ' ' << v << '\n';
        cout.flush();
    }

    return 0;
}
