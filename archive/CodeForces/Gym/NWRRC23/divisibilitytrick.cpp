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

    str s, rv = ""; cin >> s;
    ll n = stoll(s), sum = 0, cur = 0;
    for (ch c : s) sum += c - '0';
    while (cur == 0 || cur % n != 0) {
        rv += s;
        cur += sum;
    }
    cout << rv << '\n';
    return 0;
}