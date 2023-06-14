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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<ld> t(4);
    ld target;
    cin >> t[0] >> t[1] >> t[2] >> t[3] >> target;
    ssort(t);
    if (t[1] + t[2] + t[3] <= target * 3) {
        cout << "infinite\n";
        return 0;
    }
    ld rv = target * 3 - t[1] - t[2];
    if (rv >= t[0]) {
        cout << fixed << setprecision(2) << rv << '\n';
    } elif (t[0] + t[1] + t[2] <= target * 3) {
        cout << fixed << setprecision(2) << t[0] << '\n';
    } else {
        cout << "impossible\n";
    }

    return 0;
}