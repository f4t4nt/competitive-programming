#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef string str;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)

map<string, ll> eval(vector<pair<ll, str>> &sched) {
    map<string, ll> rv;
    ll prv = 0;
    for (auto [e, name] : sched) {
        rv[name] += e - prv;
        prv = e;
    }
    return rv;
}

int main() {
    vector<pair<ll, str>> sched1, sched2;
    str s, e, name;
    while (true) {
        cin >> s;
        if (s == "------") break;
        cin >> e >> name;
        sched1.pb({stoll(e), name});
    }
    while (true) {
        cin >> s;
        if (s == "======") break;
        cin >> e >> name;
        sched2.pb({stoll(e), name});
    }
    map<string, ll> times1 = eval(sched1),
        times2 = eval(sched2);
    set<string> st;
    for (auto [k, v] : times1) st.insert(k);
    for (auto [k, v] : times2) st.insert(k);
    bool ret = false;
    for (auto k : st) {
        ll v1 = times1[k], v2 = times2[k];
        if (v1 == v2) continue;
        ret = true;
        cout << k << ' ';
        if (v1 < v2) cout << '+' << v2 - v1 << '\n';
        else cout << v2 - v1 << '\n';
    }
    if (!ret) cout << "No differences found.\n";

    return 0;
}