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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;

    set<ll> nodes;
    map<ll, ll> counts;
    FOR (i, n) {
        nodes.insert(i + 1);
    }
    vector<ll> prufer_code(n - 2);
    FOR (i, n - 2) {
        cin >> prufer_code[i];
        nodes.erase(prufer_code[i]);
        counts[prufer_code[i]]++;
    }

    vector<pair<ll, ll>> edges;

    ll i = 0;
    while (sz(edges) < n - 1 && i < n - 2) {
        ll node = *nodes.begin();
        nodes.erase(node);
        edges.pb(mp(node, prufer_code[i]));
        counts[prufer_code[i]]--;
        if (counts[prufer_code[i]] == 0) {
            nodes.insert(prufer_code[i]);
        }
        i++;
    }

    ll node1 = *nodes.begin(), node2 = *nodes.rbegin();
    edges.pb(mp(node1, node2));

    FORE (edge, edges) {
        cout << edge.first << ' ' << edge.second << '\n';
    }

    return 0;
}