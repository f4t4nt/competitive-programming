#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef char ch;
typedef string str;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie();
    str s; cin >> s;
    str vowels = "aeiou";
    ll cnt = 0, y = 0;
    for (ch c : s) {
        if (c == 'y') y++;
        else if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') cnt++;
    }
    cout << cnt << ' ' << cnt + y << '\n';
}