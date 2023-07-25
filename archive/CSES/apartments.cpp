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

    ll n, m, k;
    cin >> n >> m >> k;
    vector<ll> a(n), b(m);
    FOR (i, n) {
        cin >> a[i];
    }
    FOR (i, m) {
        cin >> b[i];
    }
    ssort(a);
    ssort(b);
    ll i = 0, j = 0, rv = 0;
    while (i < n && j < m) {
        if (a[i] + k < b[j]) {
            i++;
        } elif (a[i] - k > b[j]) {
            j++;
        } else {
            i++;
            j++;
            rv++;
        }
    }
    cout << rv << '\n';

    return 0;
}