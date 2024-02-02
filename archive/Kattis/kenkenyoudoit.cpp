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

ll n, m, t;
ll ct = 0;
vector<pair<ll, ll>> cells;
vector<ll> grid(10, 0);
vector<vector<ll>> adj(10, vector<ll>());

vector<ll> pows;

void search_add(int idx, ll cur_val) {
    if (idx == m) {
        if (cur_val == 0) {
            ct++;
        }
        return;
    }

    ll prec = m - idx - 1;

    for (ll i = n; i > 0; i--) {
        
        if (cur_val > n * prec + i) continue;
        if (cur_val < prec + i) continue;

        bool works = true;
        FORE (to, adj[idx]) {
            if (grid[to] == i) {
                works = false;
                break;
            }
        }

        if (works) {
            grid[idx] = i;
            search_add(idx + 1, cur_val - i);
        }
    }
}

void search_mult(int idx, ll cur_val) {
    if (idx == m) {
        if (cur_val == 1) {
            ct++;
        }
        return;
    }

    ll prec = pows[m - idx - 1];

    for (ll i = n; i > 0; i--) {

        if (cur_val % i != 0) continue;
        if (cur_val > prec * i) continue;

        bool works = true;
        FORE (to, adj[idx]) {
            if (grid[to] == i) {
                works = false;
                break;
            }
        }

        if (works) {
            grid[idx] = i;
            search_mult(idx + 1, cur_val / i);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);   
    cout.tie(nullptr);

    cin >> n >> m >> t;
    string op;
    cin >> op;

    pows.pb(1);
    FOR (i, 10) pows.pb(pows[i] * n);

    FOR (i, m) {
        ll a, b;
        cin >> a >> b;
        cells.pb(mp(a - 1, b - 1));
    }

    ssort(cells);
    FOR (i, m) {
        FOB (j, i + 1, m) {
            if (cells[i].first == cells[j].first) adj[j].pb(i);
            if (cells[i].second == cells[j].second) adj[j].pb(i);
        }
    }

    if (op == "+") {
        search_add(0, t);
    }
    elif (op == "*") {
        search_mult(0, t);
    }
    elif (op == "-") {
        FOB (i, 1, n + 1) {
            FOB (j, 1, n + 1) {
                if (i == j) continue;
                if (abs(i - j) == t) ct++;
            }
        }
    }
    elif (op == "/") {
        FOB (i, 1, n + 1) {
            FOB (j, 1, n + 1) {
                if (i == j) continue;
                if (t * j == i) ct++;
                if (t * i == j) ct++;
            }
        }
    }

    cout << ct << "\n";

    return 0;
}