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

bool gen0(ll lo, ll hi, vector<pair<ll, ll>> &bounds, vector<ll> &trees, ll par = -1) {
    if (hi <= lo) {
        trees[lo] = par;
        return true;
    }
    ll l = lo, r = hi;
    while (l <= r) {
        if (bounds[l].first <= lo && bounds[l].second >= hi) {
            if (gen0(lo, l - 1, bounds, trees, l) &&
                gen0(l + 1, hi, bounds, trees, l)) {
                trees[l] = par;
                return true;
            } else {
                return false;
            }
        }
        if (bounds[r].first <= lo && bounds[r].second >= hi) {
            if (gen0(lo, r - 1, bounds, trees, r) &&
                gen0(r + 1, hi, bounds, trees, r)) {
                trees[r] = par;
                return true;
            } else {
                return false;
            }
        }
        l++;
        r--;
    }
    return false;
}

ll gcd(ll a, ll b) {
    if (a == 0) return b;
    return gcd(b % a, a);
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
    if (gen0(0, n - 1, bounds, tree)) {
        FOR (i, n) {
            if (i != tree[i]) {
                assert(gcd(a[i], a[tree[i]]) == 1);
            }
            cout << tree[i] + 1 << ' ';
        }
        cout << '\n';
    } else {
        cout << "impossible\n";
    }

    return 0;
}