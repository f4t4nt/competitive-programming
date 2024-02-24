#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef char ch;
typedef string str;
typedef pair<ll, ll> pll;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define ssort(C) sort(all(C))

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll tc;
    cin >> tc;

    while (tc-- > 0) {
        ll n;
        cin >> n;

        for (int i = 0; i < 70; i++) {
            ll nn = n + i;
            ll bits = __builtin_popcountll(nn);
            if (bits <= i) {
                cout << i - 1 << "\n";
                break;
            }
        }
    }

    return 0;
}