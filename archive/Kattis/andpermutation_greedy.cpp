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

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

ll mask(ll x) {
    ll rv = x;
    while (rv & (rv + 1)) {
        rv |= rv / 2;
    }
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);   
    cout.tie(nullptr);

    ll n;
    cin >> n;
    set<ll> s;
    vector<ll> a(n), rv(n);
    map<ll, ll> idxs;
    FOR (i, n) {
        cin >> a[i];
        s.insert(a[i]);
        idxs[a[i]] = i;
    }

    while (!s.empty()) {
        ll x = *s.rbegin();
        ll m = mask(x) - x;
        auto it = s.upper_bound(m);
        it--;
        ll b = 1LL << 60;
        while (*it & x) {
            while ((*it & b) == 0) {
                b /= 2;
            }
            ll b_ = b;
            while ((*it & b_ & x) == 0) {
                b_ /= 2;
            }
            m = ((*it - b_) | (b_ - 1));
            it = s.upper_bound(m);
            it--;
        }
        rv[idxs[x]] = *it;
        rv[idxs[*it]] = x;
        s.erase(x);
        s.erase(*it);
    }

    FORE (x, rv) {
        cout << x << '\n';
    }

    return 0;
}