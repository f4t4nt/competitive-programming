#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef long double ld;
typedef complex<ld> cd;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

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
        ll n, k, q; cin >> n >> k >> q;
        vector<ll> a(n);
        for (ll i = 0; i < n; i++) {
            cin >> a[i];
            a[i] -= i;
        }
        multiset<ll> cnts;
        map<ll, ll> cnt;
        vector<ll> ans(n - k + 1);
        ll i = 0;
        while (i < k) {
            if (cnt.find(a[i]) == cnt.end()) {
                cnts.insert(1);
                cnt[a[i]] = 1;
            } else {
                cnts.erase(cnts.find(cnt[a[i]]));
                cnt[a[i]]++;
                cnts.insert(cnt[a[i]]);
            }
            i++;
        }
        ans[0] = *cnts.rbegin();
        while (i < n) {
            if (a[i] != a[i - k]) {
                cnts.erase(cnts.find(cnt[a[i - k]]));
                cnt[a[i - k]]--;
                if (cnt[a[i - k]] == 0) {
                    cnt.erase(a[i - k]);
                } else {
                    cnts.insert(cnt[a[i - k]]);
                }
                if (cnt.find(a[i]) == cnt.end()) {
                    cnts.insert(1);
                    cnt[a[i]] = 1;
                } else {
                    cnts.erase(cnts.find(cnt[a[i]]));
                    cnt[a[i]]++;
                    cnts.insert(cnt[a[i]]);
                }
            }
            ans[i - k + 1] = *cnts.rbegin();
            i++;
        }
        while (q--) {
            ll l, r; cin >> l >> r;
            cout << k - ans[l - 1] << '\n';
        }
    }

    return 0;
}
