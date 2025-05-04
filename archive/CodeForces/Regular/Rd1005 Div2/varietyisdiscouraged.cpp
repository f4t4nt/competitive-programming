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
        vector<ll> a(n), freq(n + 1);
        for (ll &ai : a) cin >> ai, freq[ai]++;
        ll bestLen = 0, bestL = -1, bestR = -1;
        ll currentStart = 0, currentLen = 0;
        for (ll i = 0; i < n; i++) {
            if (freq[a[i]] == 1) {
                if (currentLen == 0) {
                    currentStart = i;
                    currentLen = 1;
                } else currentLen++;
            } else {
                if (currentLen > bestLen) {
                    bestLen = currentLen;
                    bestL = currentStart;
                    bestR = i - 1;
                }
                currentLen = 0;
            }
        }

        if (currentLen > bestLen) {
            bestLen = currentLen;
            bestL = currentStart;
            bestR = n - 1;
        }

        if (bestLen == 0) cout << 0 << '\n';
        else cout << bestL + 1 << ' ' << bestR + 1 << '\n';
    }

    return 0;
}