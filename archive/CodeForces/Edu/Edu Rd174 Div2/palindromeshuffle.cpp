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

bool valid(ll start, ll mid, ll n, str &s) {
    vector<ll> cnt(26);
    ll end = start + mid;
    ll i = start, j;
    while ((j = n - i - 1) && j >= end) {
        if (s[i] != s[j]) {
            cnt[s[i] - 'a']--;
            cnt[s[j] - 'a']++;
        }
        i++;
    }
    while (i < end) {
        if (cnt[s[i] - 'a'] > 0) cnt[s[i] - 'a']--;
        i++;
    }
    for (ll x : cnt) if (x > 0) return false;
    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        str s; cin >> s;
        ll n = sz(s), i = 0;
        while (i < n / 2 && s[i] == s[n - i - 1]) i++;
        if (i == n / 2) {
            cout << 0 << '\n';
            continue;
        }
        str s2 = s;
        flip(s2);
        ll j = n / 2 - 1;
        while (j >= 0 && s[j] == s[n - j - 1]) j--;
        ll lo = j - i + 1, hi = n - 2 * i;
        while (lo < hi) {
            ll mid = (lo + hi) / 2;
            if (valid(i, mid, n, s) ||
                valid(i, mid, n, s2)) hi = mid;
            else lo = mid + 1;
        }
        cout << lo << '\n';
    }

    return 0;
}