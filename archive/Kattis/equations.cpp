#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using cd = complex<double>;
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

constexpr ld EPS = 1e-9;

struct Eq {
    // ax + by = c
    ld x = 0, y = 0, c = 0;
    Eq(str eq) {
        istringstream iss(eq);
        ll mult = 1, neg = 1;
        str exp;
        while (iss >> exp) {
            if (exp == "=") {
                mult = -1;
                continue;
            } elif (exp == "+") {
                continue;
            } elif (exp == "-") {
                neg = -1;
                continue;
            }
            ll sgn = 1, var = 0;
            if (exp[0] == '-') {
                sgn = -1;
                exp = exp.substr(1);
            }
            if (exp.back() == 'x') {
                var = 1;
                exp.pop_back();
            } elif (exp.back() == 'y') {
                var = 2;
                exp.pop_back();
            }
            ll val = (exp.empty() ? 1 : stoll(exp));
            if (var == 0) {
                c -= sgn * mult * neg * val;
            } elif (var == 1) {
                x += sgn * mult * neg * val;
            } else {
                y += sgn * mult * neg * val;
            }
            neg = 1;
        }
    }
    bool is_valid() {
        return x != 0 || y != 0 || c == 0;
    }
    pair<ld, ld> solve() {
        return {(y == 0 && x != 0) ? c / x : 1e18, (x == 0 && y != 0) ? c / y : 1e18};
    }
};

str ld_to_frac_str(ld x) {
    if (abs(x - round(x)) < EPS) {
        return to_string((ll) round(x));
    }
    ld denom = 1, num = x;
    while (abs(num - round(num)) > EPS) {
        denom++;
        num = x * denom;
    }
    return to_string((ll) round(num)) + '/' + to_string((ll) denom);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    str line;
    getline(cin, line);
    ll t = stoll(line);
    while (t--) {
        str eq1_str, eq2_str;
        getline(cin, eq1_str);
        getline(cin, eq2_str);
        getline(cin, line);
        Eq eq1(eq1_str), eq2(eq2_str);
        ld det = eq1.x * eq2.y - eq1.y * eq2.x;
        if (det == 0) {
            if (!eq1.is_valid() || !eq2.is_valid()) {
                cout << "don't know\n";
                cout << "don't know\n";
            } else {
                ld x1, x2, y1, y2;
                tie(x1, y1) = eq1.solve();
                tie(x2, y2) = eq2.solve();
               if (x1 == 1e18 && x2 != 1e18) {
                    x1 = x2;
                } elif (x1 != 1e18 && x2 == 1e18) {
                    x2 = x1;
                } elif (x1 != x2) {
                    x1 = x2 = 1e18;
                }
                if (y1 == 1e18 && y2 != 1e18) {
                    y1 = y2;
                } elif (y1 != 1e18 && y2 == 1e18) {
                    y2 = y1;
                } elif (y1 != y2) {
                    y1 = y2 = 1e18;
                }
                cout << (x1 == 1e18 ? "don't know" : ld_to_frac_str(x1)) << '\n'
                        << (y1 == 1e18 ? "don't know" : ld_to_frac_str(y1)) << '\n';
            }
        } else {
            ld x = (eq1.c * eq2.y - eq1.y * eq2.c) / det,
                y = (eq1.x * eq2.c - eq1.c * eq2.x) / det;
            cout << ld_to_frac_str(x) << '\n' << ld_to_frac_str(y) << '\n';            
        }
        cout << '\n';
    }

    return 0;
}