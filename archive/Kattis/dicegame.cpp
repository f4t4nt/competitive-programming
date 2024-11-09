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
    ll,
    null_type,
    less<ll>,
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
// #define f first
// #define s second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FOR1(x, e) for (ll x = 1; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)

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

    ll a1, b1, a2, b2;
    cin >> a1 >> b1 >> a2 >> b2;
    ll c1, d1, c2, d2;
    cin >> c1 >> d1 >> c2 >> d2;
    map<ll, ll> probab, probcd;
    for (ll i = a1; i <= b1; i++) {
        for (ll j = a2; j <= b2; j++) {
            probab[i + j]++;
        }
    }
    for (ll i = c1; i <= d1; i++) {
        for (ll j = c2; j <= d2; j++) {
            probcd[i + j]++;
        }
    }
    ll tot = 2 * (b1 - a1 + 1) * (b2 - a2 + 1) * (d1 - c1 + 1) * (d2 - c2 + 1);
    ll res = 0;
    for (const auto& [key, val] : probab) {
        for (const auto& [key2, val2] : probcd) {
            if (key > key2) {
                res += 2 * val * val2;
            } elif (key == key2) {
                res += val * val2;
            }
        }
    }
    if (res * 2 > tot) {
        cout << "Gunnar\n";
    } elif (res * 2 < tot) {
        cout << "Emma\n";
    } else {
        cout << "Tie\n";
    }

    return 0;
}