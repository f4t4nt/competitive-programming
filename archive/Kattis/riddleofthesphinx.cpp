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
#define f first
#define s second

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

    ll q[5], ans[3];
    cout << "1 0 0\n0 1 0\n0 0 1\n1 1 1\n1 2 3\n" << endl;
    FOR (i, 5) cin >> q[i];
    if (q[0] + q[1] + q[2] == q[3]) {
        ans[0] = q[0];
        ans[1] = q[1];
        ans[2] = q[2];
    } elif (q[0] + q[1] * 2 + q[2] * 3 == q[4]) {
        ans[0] = q[0];
        ans[1] = q[1];
        ans[2] = q[2];
    } elif (q[3] * 3 - 2 * q[0] - q[1] == q[4]) {
        ans[0] = q[0];
        ans[1] = q[1];
        ans[2] = q[3] - q[0] - q[1];
    } elif (q[3] * 2 - q[0] + q[2] == q[4]) {
        ans[0] = q[0];
        ans[1] = q[3] - q[0] - q[2];
        ans[2] = q[2];
    } else {
        ans[0] = q[3] - q[1] - q[2];
        ans[1] = q[1];
        ans[2] = q[2];
    }
    FOR (i, 3) cout << ans[i] << " ";
    cout << endl;

    return 0;
}