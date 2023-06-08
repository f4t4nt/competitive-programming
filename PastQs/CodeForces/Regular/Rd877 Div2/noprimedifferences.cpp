#include <bits/stdc++.h>
    
using namespace std;
    
using ll = long long;
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
    
void fill(ll n, ll m, vector<vector<ll>> &rv) {
    ll cnt = 1;
    FOR (i, (n + 1) / 2) {
        FOR (j, m) {
            rv[i][j] = cnt++;
            assert(1 <= rv[i][j] && rv[i][j] <= n * m);
        }
        cnt += m;
    }
    cnt = m + 1;
    FOB (i, (n + 1) / 2, n) {
        FOR (j, m) {
            rv[i][j] = cnt++;
            assert(1 <= rv[i][j] && rv[i][j] <= n * m);
        }
        cnt += m;
    }
}
    
void fill2(ll n, ll m, vector<vector<ll>> &rv) {
    ll cnt = 1;
    FORR (i, (n + 1) / 2) {
        FOR (j, m) {
            rv[i][j] = cnt++;
            assert(1 <= rv[i][j] && rv[i][j] <= n * m);
        }
        cnt += m;
    }
    cnt = m + 1;
    // FOB (i, (n + 1) / 2, n) {
    for (ll i = n - 1; i >= (n + 1) / 2; i--) {
        FOR (j, m) {
            rv[i][j] = cnt++;
            assert(1 <= rv[i][j] && rv[i][j] <= n * m);
        }
        cnt += m;
    }
}
    
bool is_ok(bitset<1000005> is_prime, ll n, ll m, vector<vector<ll>> &rv) {
    FOR (i, n) {
        FOR (j, m) {
            if (i > 0 && is_prime[abs(rv[i][j] - rv[i - 1][j])]) {
                return false;
            }
            if (j > 0 && is_prime[abs(rv[i][j] - rv[i][j - 1])]) {
                return false;
            }
        }
    }
    return true;
}
    
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    bitset<1000005> is_prime;
    is_prime.set();
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i * i <= 1000000; i++) {
        if (is_prime[i]) {
            for (ll j = i * i; j <= 1000000; j += i) {
                is_prime[j] = false;
            }
        }
    }
    
    ll t;
    cin >> t;
    while (t--) {
        ll n, m;
        cin >> n >> m;
        vector<vector<ll>> rv(n, vector<ll>(m)), tmp = vector<vector<ll>>(m, vector<ll>(n));
        fill(n, m, rv);
        bool ok = is_ok(is_prime, n, m, rv);
        if (!ok) {
            fill2(n, m, rv);
            ok = is_ok(is_prime, n, m, rv);
        }
        if (!ok) {
            fill(m, n, tmp);
            FOR (i, n) {
                FOR (j, m) {
                    rv[i][j] = tmp[j][i];
                }
            }
            ok = is_ok(is_prime, n, m, rv);
        }
        if (!ok) {
            fill2(m, n, tmp);
            FOR (i, n) {
                FOR (j, m) {
                    rv[i][j] = tmp[j][i];
                }
            }
            ok = is_ok(is_prime, n, m, rv);
        }
        assert(ok);
        FOR (i, n) {
            FOR (j, m) {
                cout << rv[i][j] << ' ';
            }
            cout << '\n';
        }
    }
    
    return 0;
}