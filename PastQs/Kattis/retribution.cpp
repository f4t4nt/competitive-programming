#include <bits/stdc++.h>

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
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m, p;
    cin >> n >> m >> p;
    vector<pair<ll, ll>> judges(n), repos(m), storehouses(p);
    FOR (i, n) {
        cin >> judges[i].first >> judges[i].second;
    }
    FOR (i, m) {
        cin >> repos[i].first >> repos[i].second;
    }
    FOR (i, p) {
        cin >> storehouses[i].first >> storehouses[i].second;
    }

    set<tuple<ld, ll, ll>> judge_repo, judge_storehouse;
    FOR (i, n) {
        FOR (j, m) {
            ld dist = sqrt(
                (ld) (judges[i].first - repos[j].first) * (judges[i].first - repos[j].first) +
                (ld) (judges[i].second - repos[j].second) * (judges[i].second - repos[j].second)
            );
            judge_repo.insert(mt(dist, i, j));
        }
    }
    FOR (i, n) {
        FOR (j, p) {
            ld dist = sqrt(
                (ld) (judges[i].first - storehouses[j].first) * (judges[i].first - storehouses[j].first) +
                (ld) (judges[i].second - storehouses[j].second) * (judges[i].second - storehouses[j].second)
            );
            judge_storehouse.insert(mt(dist, i, j));
        }
    }


    vector<ld> repo_assignments(m, -1), storehouse_assignments(p, -1);
    // 0 = not assigned, 1 = assigned to repo, 2 = assigned to storehouse and repo
    vector<ll> judge_assigned(n, 0);

    // want to assign all judges to both repo and storehouse
    FORE (i, judge_repo) {
        ll judge = get<1>(i), repo = get<2>(i);
        if (judge_assigned[judge] == 0 && repo_assignments[repo] == -1) {
            judge_assigned[judge] = 1;
            repo_assignments[repo] = get<0>(i);
        }
    }
    FORE (i, judge_storehouse) {
        ll judge = get<1>(i), storehouse = get<2>(i);
        if (judge_assigned[judge] == 1 && storehouse_assignments[storehouse] == -1) {
            judge_assigned[judge] = 2;
            storehouse_assignments[storehouse] = get<0>(i);
        }
    }

    // find sum of all distances
    ld rv = 0;
    FOR (i, m) {
        if (repo_assignments[i] != -1) {
            rv += repo_assignments[i];
        }
    }
    FOR (i, p) {
        if (storehouse_assignments[i] != -1) {
            rv += storehouse_assignments[i];
        }
    }

    cout << fixed << setprecision(10) << rv << '\n';

    return 0;
}