#include <algorithm>
#include <cmath>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <list>
#include <map>
#include <math.h>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <string>
#include <string.h>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>

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
#define flip(C) reverse(C.begin(), C.end())
#define ssort(C) sort(C.begin(), C.end())
#define rsort(C) sort(C.begin(), C.end(), greater<>())

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

struct offer {
    ll buy, sell;
    ld ratio;
};

int main () {
    ll t;
    cin >> t;
    while (t--) {
        ll offer_count, food_count, surplus, demand;
        cin >> offer_count >> food_count >> surplus >> demand;
        surplus--, demand--;
        vector<offer> offers(offer_count);
        FOR (i, offer_count) {
            cin >> offers[i].buy >> offers[i].sell >> offers[i].ratio;
            offers[i].buy--, offers[i].sell--;
        }
        vector<vector<offer>> adj(food_count), adj_rev(food_count);
        FORE (o, offers) {
            adj[o.buy].pb(o);
            adj_rev[o.sell].pb(o);
        }
        vector<bool> from_surplus(food_count), to_demand(food_count);
        queue<ll> q;
        q.push(surplus);
        while (!q.empty()) {
            ll cur = q.front();
            q.pop();
            if (from_surplus[cur]) continue;
            from_surplus[cur] = true;
            FORE (o, adj[cur]) {
                q.push(o.sell);
            }
        }
        q.push(demand);
        while (!q.empty()) {
            ll cur = q.front();
            q.pop();
            if (to_demand[cur]) continue;
            to_demand[cur] = true;
            FORE (o, adj_rev[cur]) {
                q.push(o.buy);
            }
        }
        vector<bool> relevant(food_count);
        FOR (i, food_count) {
            relevant[i] = from_surplus[i] && to_demand[i];
        }
        vector<ld> dist(food_count, -1e18);
        dist[surplus] = 0;
        FOR (i, food_count) {
            FORE (o, offers) {
                if (relevant[o.buy] && relevant[o.sell]) {
                    dist[o.sell] = max(dist[o.sell], dist[o.buy] + o.ratio);
                }
            }
        }
        bool neg_cycle = false;
        FORE (o, offers) {
            if (relevant[o.buy] && relevant[o.sell]) {
                if (dist[o.sell] < dist[o.buy] + o.ratio) {
                    neg_cycle = true;
                    break;
                }
            }
        }
        if (neg_cycle) {
            cout << "TRUE\n";
        } else {
            cout << "FALSE\n";
        }
    }
    return 0;
}