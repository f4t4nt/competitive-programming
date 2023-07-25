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

    ll n, t, rv = 0;
    cin >> n >> t;
    vector<ll> x(n), pos(n + 2, n), ref(n + 2);
    FOR (i, n) {
        cin >> x[i];
        pos[x[i]] = i;
    }
    FOR (i, n) {
        if (pos[i + 1] < pos[i]) {
            ref[i + 1] = 1;
            rv++;
        }
    }
    while (t--) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        ll xa = x[a], xb = x[b];
        assert(ref[xa] == a < pos[xa - 1]);
        assert(ref[xa + 1] == a > pos[xa + 1]);
        assert(ref[xb] == b < pos[xb - 1]);
        assert(ref[xb + 1] == b > pos[xb + 1]);
        swap(x[a], x[b]);
        swap(pos[xa], pos[xb]);
        swap(a, b);
        ll del = 0;
        del += (ref[xa] - (a < pos[xa - 1]));
        ref[xa] = a < pos[xa - 1];
        del += (ref[xa + 1] - (a > pos[xa + 1]));
        ref[xa + 1] = a > pos[xa + 1];
        del += (ref[xb] - (b < pos[xb - 1]));
        ref[xb] = b < pos[xb - 1];
        del += (ref[xb + 1] - (b > pos[xb + 1]));
        ref[xb + 1] = b > pos[xb + 1];
        rv -= del;
        cout << rv << '\n';
    }

    return 0;
}