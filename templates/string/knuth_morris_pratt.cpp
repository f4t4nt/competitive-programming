#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef string str;

#define pb push_back
#define sz(C) (ll) C.size()

// prefix function pi[i]: length of longest proper prefix of s[0..i]
// that is also a suffix of s[0..i]
// O(m) time complexity
vector<ll> prefix_function(str &s) {
    ll n = sz(s);
    vector<ll> pi(n);
    for (ll i = 1, j = 0; i < n; i++) {
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}

// returns list of start positions where pattern p occurs in text t
// O(n + m) time complexity
vector<ll> kmp_search(str &p, str &t) {
    vector<ll> pi = prefix_function(p);
    vector<ll> res;
    ll n = sz(t), m = sz(p), j = 0;
    for (ll i = 0; i < n; i++) {
        while (j > 0 && t[i] != p[j]) j = pi[j - 1];
        if (t[i] == p[j]) j++;
        if (j == m) {
            res.pb(i - m + 1); // match ends at i
            j = pi[j - 1];
        }
    }
    return res;
}
