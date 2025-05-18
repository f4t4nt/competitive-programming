#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef complex<long double> cd;
typedef long double ld;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

using indexed_set = tree<
    pld,
    null_type,
    less<pld>,
    rb_tree_tag,
    tree_order_statistics_node_update>;

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
// #define f first
// #define s second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)

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
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m; cin >> n >> m;
    vector<string> db1, db2;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        db1.push_back(s);
    }
    for (int i = 0; i < m; i++) {
        string s; cin >> s;
        db2.push_back(s);
    }

    vector<pair<int, int>> res;

    // for (int i = 0; i < n; i++)
    //     for (int j = 0; j < m; j++)
    //         if (db1[i] == db2[j])
    //             res.push_back({i, j});

    bool swapped = false;
    if (n > m) {
        swap(db1, db2);
        swap(n, m);
        swapped = true;
    }

    auto pt1 = chrono::steady_clock::now();

    unordered_map<string, vector<int>> db1_hash;
    for (int i = 0; i < n; i++) {
        db1_hash[db1[i]].push_back(i);
    }

    auto pt2 = chrono::steady_clock::now();

    #pragma omp parallel
    {
        vector<pair<int, int>> cur_res;
        #pragma omp for nowait
        for (int j = 0; j < m; j++) {
            auto it = db1_hash.find(db2[j]);
            if (it == db1_hash.end()) continue;
            for (int i : it->second) {
                if (swapped) cur_res.push_back({i, j});
                else cur_res.push_back({j, i});
            }
        }
        #pragma omp critical
        res.insert(res.end(), cur_res.begin(), cur_res.end());
    }

    auto pt3 = chrono::steady_clock::now();
    double step1 = chrono::duration<double, milli>(pt2 - pt1).count();
    cerr << step1 << "ms\n";
    double step2 = chrono::duration<double, milli>(pt3 - pt1).count();
    cerr << step2 << "ms\n";
    
    cerr << res.size() << '\n';
    for (auto [i, j] : res) cout << i << ' ' << j << '\n';

    return 0;
}