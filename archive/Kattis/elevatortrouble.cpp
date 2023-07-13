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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll f, s, t, u, d;
    cin >> f >> s >> t >> u >> d;
    s--, t--;
    vector<ll> dist(f, 1e18);
    dist[s] = 0;
    queue<ll> q;
    q.push(s);
    while (!q.empty()) {
        ll v = q.front();
        q.pop();
        if (v + u < f && dist[v + u] > dist[v] + 1) {
            dist[v + u] = dist[v] + 1;
            q.push(v + u);
        }
        if (v - d >= 0 && dist[v - d] > dist[v] + 1) {
            dist[v - d] = dist[v] + 1;
            q.push(v - d);
        }
    }
    if (dist[t] == 1e18) {
        cout << "use the stairs\n";
    } else {
        cout << dist[t] << '\n';
    }

    return 0;
}