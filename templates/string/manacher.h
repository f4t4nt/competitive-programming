#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef string str;
typedef char ch;
typedef pair<ll, ll> pll;

#define sz(C) (ll) C.size()

// -----------------------------------------------------------------------------
//  Manacher
// -----------------------------------------------------------------------------
//  Supports:   - manacher_p(s)  radii over t = "$#a#b#c#..."; p[i] is the
//                length in s of the longest palindrome of t centered at i,
//                starting at (i - p[i]) / 2; '#' centers give even
//                palindromes, letter centers odd
//  Notes:      - manacher(s)  longest palindromic substring of s, returns
//                {length, start index}
//  Complexity: O(n)
// -----------------------------------------------------------------------------
vector<ll> manacher_p(str &s) {
    str t = "$#";
    for (ch c : s) t += c, t += '#';
    ll n = sz(t);
    vector<ll> p(n);
    ll center = 0, max_rad = -1;
    for (ll i = 1; i < n; i++) {
        ll rad = (i <= max_rad ? min(p[2 * center - i], max_rad - i) : 0);
        while (i - rad - 1 >= 0 && i + rad + 1 < n && t[i - rad - 1] == t[i + rad + 1]) rad++;
        p[i] = rad;
        if (i + rad > max_rad) {
            center = i;
            max_rad = i + rad;
        }
    }
    return p;
}

pll manacher(str &s) {
    vector<ll> p = manacher_p(s);
    ll len = 0, idx = 0;
    for (ll i = 1; i < sz(p); i++)
        if (p[i] > len) len = p[i], idx = i;
    return { len, (idx - len) / 2 };
}
