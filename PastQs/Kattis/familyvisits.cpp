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

ll sim(ll d0, ll df, vector<ll> &m, vector<ll> &c)
{
    ll rv = 0, mess = 0, clean = 0;
    priority_queue<ll> pq;
    for (ll d = df - 1; d >= d0; d--) {
        mess += m[d];
        pq.push(c[d]);
        while (mess > clean && !pq.empty()) {
            ll tv = pq.top();
            pq.pop();
            clean += tv;
            rv++;
        }
        if (clean >= mess) {
            clean -= mess;
            mess = 0;
        } else {
            return 1e18;
        }
    }
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);   
    cout.tie(nullptr);

    ll n, d;
    cin >> n >> d;
    vector<ll> m(n), c(n);
    FOR (i, n) {
        cin >> m[i] >> c[i];
    }
    vector<ll> days(d + 1);
    FOR (i, d) {
        cin >> days[i + 1];
    }

    ll rv = 0;
    FOR (i, d) {
        ll tv = sim(days[i], days[i + 1], m, c);
        if (tv == 1e18) {
            cout << -1 << '\n';
            return 0;
        } else {
            rv += tv;
        }
    }
    cout << rv << '\n';

    return 0;
}