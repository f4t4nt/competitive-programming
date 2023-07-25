#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using db = double;
using cd = complex<double>;
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

    ll n, k;
    cin >> n >> k;
    vector<ll> p(n);
    map<ll, ll> cnts;
    multiset<ll> rem;
    FOR (i, n) {
        cin >> p[i];
        cnts[p[i]]++;
        rem.insert(p[i]);
    }
    ssort(p);
    vector<vector<ll>> rv;
    FOR (i, n) {
        if (cnts[p[i]] == 0) {
            continue;
        }
        vector<ll> tmp = {p[i]};
        cnts[p[i]]--;
        rem.erase(rem.find(p[i]));
        auto it = rem.upper_bound(k - p[i]);
        if (it != rem.begin()) {
            it--;
            tmp.pb(*it);
            cnts[*it]--;
            rem.erase(it);
        }
        rv.pb(tmp);
    }
    cout << sz(rv) << '\n';

    return 0;
}