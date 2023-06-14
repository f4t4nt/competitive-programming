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

// https://open.kattis.com/problems/factorfree

constexpr ll MAX_A = 1e7 + 1;
vector<bool> sieve(MAX_A);
set<ll> primes;

bool gen(ll lo, ll hi, vector<pair<ll, ll>> &bounds, vector<ll> &trees, ll par = -1) {
    if (hi <= lo) {
        trees[lo] = par;
        return true;
    }
    FOB (i, lo, hi + 1) {
        if (bounds[i].first <= lo && bounds[i].second >= hi) {
            if (gen(lo, i - 1, bounds, trees, i) &&
                gen(i + 1, hi, bounds, trees, i)) {
                trees[i] = par;
                return true;
            }
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    FOB (x, 2, MAX_A) {
        if (!sieve[x]) {
            for (ll y = 2 * x; y < MAX_A; y += x) {
                sieve[y] = true;
            }
            primes.insert(x);
        }
    }

    ll n;
    cin >> n;
    vector<ll> a(n);
    FOR (i, n) {
        cin >> a[i];
    }
    vector<set<ll>> ref_a(n);
    map<ll, set<ll>> ref_p;
    FOR (i, n) {
        ll x = a[i];
        FORE (p, primes) {
            if (x % p == 0) {
                ref_a[i].insert(p);
                ref_p[p].insert(i);
                while (x % p == 0) {
                    x /= p;
                }
            }
            if (p * p > x) {
                break;
            }
        }
        if (x > 1) {
            ref_a[i].insert(x);
            ref_p[x].insert(i);
        }
    }
    vector<pair<ll, ll>> bounds(n, {0, n - 1});
    map<ll, ll> prev;
    FOR (i, n) {
        FORE (p, ref_a[i]) {
            if (prev.find(p) != prev.end()) {
                bounds[i].first = max(bounds[i].first, prev[p] + 1);
            }
            prev[p] = i;
        }
    }
    prev.clear();
    FORR (i, n) {
        FORE (p, ref_a[i]) {
            if (prev.find(p) != prev.end()) {
                bounds[i].second = min(bounds[i].second, prev[p] - 1);
            }
            prev[p] = i;
        }
    }
    vector<ll> tree(n, -1);
    if (gen(0, n - 1, bounds, tree)) {
        FORE (t, tree) {
            cout << t + 1 << ' ';
        }
        cout << '\n';
    } else {
        cout << "impossible\n";
    }

    return 0;
}