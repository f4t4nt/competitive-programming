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
    ll n, s, t, max_a = 0;
    cin >> n;
    vector<ll> a(n);
    FOR (i, n) {
        cin >> a[i];
        max_a = max(max_a, a[i]);
    }
    cin >> s >> t;
    s--, t--;
    vector<ll> min_primes(max_a + 1), primes;
    FOB (i, 2, max_a + 1) {
        if (min_primes[i] == 0) {
            min_primes[i] = i;
            primes.pb(i);
        }
        FORE (prime, primes) {
            if (i * prime > max_a) {
                break;
            }
            min_primes[i * prime] = prime;
        }
    }
    map<ll, ll> prime_to_idx;
    FOR (i, sz(primes)) {
        prime_to_idx[primes[i]] = i;
    }
    ll m = sz(primes);
    vector<vector<ll>> adj(n + m);
    FOR (i, n) {
        ll tmp = a[i];
        while (tmp > 1) {
            ll prime = min_primes[tmp];
            adj[i].pb(n + prime_to_idx[prime]);
            adj[n + prime_to_idx[prime]].pb(i);
            while (tmp % prime == 0) {
                tmp /= prime;
            }
        }
    }
    vector<ll> dist(n + m, -1), par(n + m, -1);
    queue<ll> q;
    q.push(s);
    dist[s] = 0;
    while (!q.empty()) {
        ll v = q.front();
        q.pop();
        FORE (u, adj[v]) {
            if (dist[u] == -1) {
                dist[u] = dist[v] + 1;
                par[u] = v;
                q.push(u);
            }
        }
    }
    if (dist[t] == -1) {
        cout << -1 << endl;
    } else {
        vector<ll> path;
        ll v = t;
        while (v != -1) {
            if (v < n) {
                path.pb(v);
            }
            v = par[v];
        }
        flip(path);
        cout << sz(path) << '\n';
        FORE (v, path) {
            cout << v + 1 << ' ';
        }
        cout << '\n';
    }
    return 0;
}