#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef complex<long double> cd;
typedef long double ld;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

using indexed_set = tree<
    pld,
    null_type,
    less<pld>,
    rb_tree_tag,
    tree_order_statistics_node_update>;

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
#define x first
#define y second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)
#define FOB(x, b, e) for (auto x = b; x < e; x++)
#define FORE(x, C) for (auto &x : C)

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
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    str a, op, b, eq, c;
    cin >> a >> op >> b >> eq >> c;
    FOR (i, sz(a)) {
        FOR (j, sz(b)) {
            if (i == 0 && j == 0) continue;
            str a_new = b.substr(0, j) + a.substr(i, sz(a) - i),
                b_new = a.substr(0, i) + b.substr(j, sz(b) - j);
            if (op == "*" && stoll(a_new) * stoll(b_new) == stoll(c)) {
                cout << a_new << " * " << b_new << " = " << c << '\n';
                return 0;
            } elif (op == "+" && stoll(a_new) + stoll(b_new) == stoll(c)) {
                cout << a_new << " + " << b_new << " = " << c << '\n';
                return 0;
            }
        }
        FOR (j, sz(c)) {
            if (i == 0 && j == 0) continue;
            str a_new = c.substr(0, j) + a.substr(i, sz(a) - i),
                c_new = a.substr(0, i) + c.substr(j, sz(c) - j);
            if (op == "*" && stoll(a_new) * stoll(b) == stoll(c_new)) {
                cout << a_new << " * " << b << " = " << c_new << '\n';
                return 0;
            } elif (op == "+" && stoll(a_new) + stoll(b) == stoll(c_new)) {
                cout << a_new << " + " << b << " = " << c_new << '\n';
                return 0;
            }
        }
    }
    FOR (i, sz(b)) {
        FOR (j, sz(c)) {
            if (i == 0 && j == 0) continue;
            str b_new = c.substr(0, j) + b.substr(i, sz(b) - i),
                c_new = b.substr(0, i) + c.substr(j, sz(c) - j);
            if (op == "*" && stoll(a) * stoll(b_new) == stoll(c_new)) {
                cout << a << " * " << b_new << " = " << c_new << '\n';
                return 0;
            } elif (op == "+" && stoll(a) + stoll(b_new) == stoll(c_new)) {
                cout << a << " + " << b_new << " = " << c_new << '\n';
                return 0;
            }
        }
    }
    assert(false);

    return 0;
}