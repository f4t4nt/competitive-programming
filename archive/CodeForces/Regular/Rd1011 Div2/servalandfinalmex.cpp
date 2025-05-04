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
#define f first
#define s second

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

    ll t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        vector<ll> a(n);
        for (ll &ai : a) cin >> ai;
        ll left = -1, right = -1;
        for (ll i = 0; i < n; ++i) {
            if (a[i] == 0) {
                if (left == -1) left = i;
                right = i;
            }
        }
        if (left == -1) {
            cout << 1 << "\n";
            cout << 1 << " " << n << "\n";
            continue;
        }
        if (left == 0 && right == n - 1) {
            cout << 3 << "\n";
            cout << 3 << " " << n << "\n";
            cout << 1 << " " << 2 << "\n";
            cout << 1 << " " << 2 << "\n";
        } else if (left == 0) {
            cout << 2 << "\n";
            cout << 1 << " " << n - 1 << "\n";
            cout << 1 << " " << 2 << "\n";
        } else {
            if (left == n - 1) {
                left--;
            }
            cout << 2 << "\n";
            cout << left + 1 << " " << n << "\n";
            cout << 1 << " " << left + 1 << "\n";
        }
    }

    return 0;
}