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
// #define x first
// #define y second

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

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while(t--) {
        ll n, m; cin >> n >> m;
        vector<ll> a(n), b(m);
        ll sum_a = 0, sum_b = 0;
        FOR (i, n) {
            cin >> a[i];
            sum_a += a[i];
        }
        FOR (j, m) {
            cin >> b[j];
            sum_b += b[j];
        }
        if (sum_a != sum_b) {
            cout << "No\n";
            continue;
        }
        map<ll, ll> freq_a;
        for (ll &x : a) freq_a[x]++;
        std::priority_queue<ll> pq;
        for (ll &x : b) pq.push(x);
        ll merges_needed = n - m, splits_used = 0;
        bool ok = true;
        while (!pq.empty()) {
            ll x = pq.top(); pq.pop();
            if (freq_a.count(x) && freq_a[x] > 0) {
                freq_a[x]--;
                if (freq_a[x] == 0) freq_a.erase(x);
            } else {
                if (x == 1) {
                    ok = false;
                    break;
                }
                if (splits_used == merges_needed) {
                    ok = false;
                    break;
                }
                splits_used++;
                ll lo = x / 2, hi = (x + 1) / 2;
                pq.push(lo), pq.push(hi);
            }
        }
        if (!ok) {
            cout << "No\n";
        } elif (!freq_a.empty()) {
            cout << "No\n";
        } elif (splits_used <= merges_needed) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }

    return 0;
}