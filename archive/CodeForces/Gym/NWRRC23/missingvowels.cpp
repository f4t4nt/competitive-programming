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

    string a, b;
    cin >> a >> b;

    ll a_idx = 0, b_idx = 0;

    for (int i = 0; i < sz(a); i++) {
        if (a[i] >= 'A' && a[i] <= 'Z') a[i] += 'a' - 'A';
    }
    for (int i = 0; i < sz(b); i++) {
        if (b[i] >= 'A' && b[i] <= 'Z') b[i] += 'a' - 'A';
    }

    while (a_idx < sz(a) && b_idx < sz(b)) {
        if (a[a_idx] == b[b_idx]) {
            a_idx++;
            b_idx++;
        }
        else if (b[b_idx] == 'a' || b[b_idx] == 'e' ||
                b[b_idx] == 'i' || b[b_idx] == 'o' ||
                b[b_idx] == 'u' || b[b_idx] == 'y') {
                    b_idx++;
                }
        else {
            break;
        }
    }

    while (b_idx < sz(b)) {
        if (b[b_idx] == 'a' || b[b_idx] == 'e' ||
                b[b_idx] == 'i' || b[b_idx] == 'o' ||
                b[b_idx] == 'u' || b[b_idx] == 'y') {
                    b_idx++;
        }
        else {
            break;
        }
    }

    if (a_idx == sz(a) && b_idx == sz(b)) {
        cout << "Same\n";
    }
    else {
        cout << "Different\n";
    }

    return 0;
}