#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ull = unsigned long long;
using ld = long double;
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

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, total_price;
    cin >> n >> total_price;
    vector<ll> prices(n), pages(n), copies(n);
    FOR(i, n) cin >> prices[i];
    FOR(i, n) cin >> pages[i];
    FOR(i, n) cin >> copies[i];
    // dp[price] = max # of pages
    vector<ll> dp(total_price + 1, -1e18);
    dp[0] = 0;
    FOR (i, n) {
        ll cur_copies = 0;
        while (copies[i] > 0) {
            cur_copies = min(copies[i], cur_copies + 1);
            copies[i] -= cur_copies;
            ll cur_pages = cur_copies * pages[i];
            ll cur_price = cur_copies * prices[i];
            for (ll j = total_price; j >= cur_price; j--) {
                dp[j] = max(dp[j], dp[j - cur_price] + cur_pages);
            }
        }
    }
    cout << *max_element(all(dp)) << '\n';

    return 0;
}