#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef complex<long double> cd;
typedef long double ld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

using indexed_set = tree<
    pair<ll, ll>,
    null_type,
    less<pair<ll, ll>>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for(ll x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
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

ll get_subsum(ll &deg, map<ll, set<ll>> &degs) {
    assert(degs.count(deg) && sz(degs[deg]) > 0);
    if (sz(degs[deg]) == 1) {
        auto left = degs.lower_bound(deg), right = degs.upper_bound(deg);
        if (left == degs.begin()) {
            left = degs.end();
        }
        left--;
        if (right == degs.end()) {
            right = degs.begin();
        }
        return (right->first - left->first + 359) % 360 + 1;
    } else {
        return 0;
    }
}

void get_sum(ll id, map<ll, ll> &id_maps, vector<vector<ll>> &cards, vector<map<ll, set<ll>>> &degs, vector<ll> &sums) {
    ll idx = id_maps[id];
    sums[idx] = 0;
    FOR (j, 3) {
        ll deg = cards[idx][j];
        sums[idx] += get_subsum(deg, degs[j]);
    }
}

void remove_and_update(
    ll &id,
    map<ll, ll> &id_maps,
    vector<vector<ll>> &cards,
    vector<map<ll, set<ll>>> &degs,
    vector<ll> &sums,
    __gnu_pbds::priority_queue<pair<ll, ll>> &pq,
    vector<__gnu_pbds::priority_queue<pair<ll, ll>>::point_iterator> &ptrs
) {
    ll idx = id_maps[id];
    set<ll> upd;
    FOR (j, 3) {
        ll deg = cards[idx][j];
        degs[j][deg].erase(id);
        if (sz(degs[j][deg]) == 0) {
            degs[j].erase(deg);
            if (sz(degs[j]) == 0) {
                continue;
            }
            auto left = degs[j].lower_bound(deg), right = degs[j].upper_bound(deg);
            if (left == degs[j].begin()) {
                left = degs[j].end();
            }
            left--;
            if (right == degs[j].end()) {
                right = degs[j].begin();
            }
            if (sz(left->second) < 2) {
                FORE (jd, left->second) {
                    upd.insert(jd);
                }
            }
            if (sz(right->second) < 2) {
                FORE (jd, right->second) {
                    upd.insert(jd);
                }
            }
        } elif (sz(degs[j][deg]) < 2) {
            FORE (jd, degs[j][deg]) {
                upd.insert(jd);
            }
        }
    }
    FORE (jd, upd) {
        get_sum(jd, id_maps, cards, degs, sums);
        ll jdx = id_maps[jd];
        pq.modify(ptrs[jdx], {-sums[jdx], jd});
    }
}

str get_pq(__gnu_pbds::priority_queue<pair<ll, ll>> pq) {
    str rv = "";
    while (sz(pq) > 0) {
        auto [sum, id] = pq.top();
        pq.pop();
        rv += "(" + to_string(-sum) + ", " + to_string(id) + ")";
    }
    return rv;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    map<ll, ll> id_maps;
    vector<map<ll, set<ll>>> degs(3);
    vector<vector<ll>> cards(n);
    FOR (idx, n) {
        ll rgb[3], id;
        FOR (j, 3) cin >> rgb[j];
        cin >> id;
        cards[idx] = {rgb[0], rgb[1], rgb[2], id};
        id_maps[id] = idx;
        FOR (j, 3) degs[j][rgb[j]].insert(id);
    }
    vector<ll> sums(n);
    FOR (idx, n) {
        get_sum(cards[idx][3], id_maps, cards, degs, sums);
    }
    vector<__gnu_pbds::priority_queue<pair<ll, ll>>::point_iterator> ptrs(n);
    __gnu_pbds::priority_queue<pair<ll, ll>> pq;
    FOR (idx, n) {
        ptrs[idx] = pq.push({-sums[idx], cards[idx][3]});
    }
    vector<ll> rv;
    while (sz(pq) > 0) {
        auto [sum, id] = pq.top();
        pq.pop();
        rv.pb(id);
        remove_and_update(id, id_maps, cards, degs, sums, pq, ptrs);
    }
    FORE (id, rv) cout << id << '\n';

    return 0;
}