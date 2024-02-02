#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long long ld;
typedef complex<ld> cd;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define ssort(C) ssort(all(C))

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)

int main() {
    ll n, x; cin >> n >> x;
    vector<ll> a(n);
    FOR (i, n) cin >> a[i];
    vector<ll> dist(n, 1e18);
    priority_queue<tuple<ll, ll>> q;

    FOR(i, n) {
        ll to = (i + a[0]) % n;
        dist[to] = i + 1;
        q.push({-(i + 1), to});
    }

    while (sz(q)) {
        auto [d, idx] = q.top(); q.pop();
        d = -d;
        if (idx == x) {
            break;
        }
        
        ll to = (idx + a[idx]) % n;
        if (dist[to] > d + 1) {
            dist[to] = d + 1;
            q.push({-dist[to], to});
        }

        to = (idx + 1) % n;
        if (dist[to] > d + 1) {
            dist[to] = d + 1;
            q.push({-dist[to], to});
        }
        
    }

    cout << dist[x] << "\n";
    return 0;
}