#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

struct SlidingGCD {
    stack<pll> l, r;

    void push(ll x) {
        ll g = r.empty() ? x : __gcd(r.top().first, x);
        r.push({g, x});
    }

    void pop() {
        if (l.empty()) {
            while (!r.empty()) {
                ll v = r.top().second; r.pop();
                ll g = l.empty() ? v : __gcd(l.top().first, v);
                l.push({g, v});
            }
        }
        assert(!l.empty());
        l.pop();
    }

    ll get() {
        ll gl = l.empty() ? 0 : l.top().first;
        ll gr = r.empty() ? 0 : r.top().first;
        return __gcd(gl, gr);
    }
};
