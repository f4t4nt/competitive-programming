#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;
using ch = char;
using str = string;

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

// https://open.kattis.com/problems/kitesurfing

constexpr ll INF = 1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    if (false) {
        ll s, d, t, n;
        cin >> s >> d >> t >> n;
        vector<pair<ll, ll>> islands(n);
        FOR (i, n) {
            cin >> islands[i].first >> islands[i].second;
        }
        islands.pb({0,0});
        islands.pb({s,s+1});
        ssort(islands);
        map<ll, ll> dists, parents;
        FOB (i, 1, n + 1) {
            dists[islands[i].second] = INF;
            if (islands[i].second - d > islands[i - 1].second) {
                dists[islands[i].second - d] = INF - 1;
            }
            dists[islands[i].first] = INF - 1;
            if (islands[i].first + d < islands[i + 1].first) {
                dists[islands[i].first + d] = INF - 1;
            }
        }
        dists[0] = 0;
        dists[s] = INF - 1;
        set<ll> prev_seg, cur_seg = {0};
        auto it = next(dists.begin());
        while (it != dists.end()) {
            bool jump = it->second == INF;
            if (jump) {
                FORE (i, cur_seg) {
                    prev_seg .insert(i);
                }
                cur_seg.clear();
            }
            while (!prev_seg.empty() && *prev_seg.begin() < it->first - d) {
                prev_seg.erase(prev_seg.begin());
            }
            FORE (i, cur_seg) {
                // it->second = min({
                //     it->second,
                //     dists[i] + it->first - i,
                //     dists[i] + (it->first - i) / d * t + (it->first - i) % d,
                //     dists[i] + (it->first - i + d - 1) / d * t
                // });
                if (it->second > dists[i] + it->first - i ||
                    it->second > dists[i] + (it->first - i) / d * t + (it->first - i) % d ||
                    it->second > dists[i] + (it->first - i + d - 1) / d * t)
                {
                    it->second = min({
                        dists[i] + it->first - i,
                        dists[i] + (it->first - i) / d * t + (it->first - i) % d,
                        dists[i] + (it->first - i + d - 1) / d * t
                    });
                    parents[it->first] = i;
                }
            }
            FORE (i, prev_seg) {
                // assert(i + d >= it->first);
                // it->second = min(it->second, dists[i] + (it->first - i + d - 1) / d * t);
                if (it->second > dists[i] + (it->first - i + d - 1) / d * t) {
                    it->second = dists[i] + (it->first - i + d - 1) / d * t;
                    parents[it->first] = i;
                }
            }
            cur_seg.insert(it->first);
            it++;
        }
        FORE (i, parents) {
            cout << i.first << ": " << i.second << '\n';
        }
        FORE (i, dists) {
            cout << i.first << ": " << i.second << '\n';
        }
        cout << dists[s] << '\n';
    } else {
        int S, D, C, N;
        cin >> S >> D >> C >> N;
        
        vector<int> L(N+1), R(N+1);
        for (int i = 0; i < N; i++) {
            cin >> R[i] >> L[i+1];
        }
        R[N] = S;
        
        /* If we start jumping at L[i] until we reach island j,
        * where do we first land and how many jumps do we need?
        */
        auto jump = [&](int i, int j) {
            int pos = L[i], cnt = 0, k = i;
            while (k < j) {
                if (pos+D <= R[k]) {
                    int t = (R[k]-pos)/D;
                    pos += t*D, cnt += t;
                } else if (pos+D < L[k+1]) {
                    pos = R[k], cnt++;
                } else {
                    while (k < j && L[k+1] <= pos+D) k++;
                    pos = min(pos+D,R[k]), cnt++;
                }
            }
            return make_pair(pos,cnt);
        };
        
        /* What is the fastest way to cover a certain distance
        * when only moving over land?
        */
        auto dry_distance = [&](int from, int to) {
            if (from > to) return 0LL;
            long long dist = to-from, k = dist/D;
            return min(dist, min((k+1)*C, k*C + dist%D));
        };

        vector<long long> dp(N+1,LLONG_MAX/2), par(N+1);
        
        for (int i = N; i >= 0; i--) {
            for (int j = i; j <= N; j++) {
                auto [first_pos, jump_count] = jump(i,j);
                long long jump_cost = jump_count * 1LL * C;
                
                if (j == N) {
                    // dp[i] = min(dp[i], jump_cost + dry_distance(first_pos,R[N]));
                    if (dp[i] > jump_cost + dry_distance(first_pos,R[N])) {
                        dp[i] = jump_cost + dry_distance(first_pos,R[N]);
                        par[i] = j;
                    }
                } else {
                    for (int k = j+1; k <= N; k++) {
                        int last_pos = L[k]-D;
                        if (last_pos > R[j]) break;
                        // dp[i] = min(dp[i], jump_cost + dry_distance(first_pos, last_pos) + C + dp[k]);
                        if (dp[i] > jump_cost + dry_distance(first_pos, last_pos) + C + dp[k]) {
                            dp[i] = jump_cost + dry_distance(first_pos, last_pos) + C + dp[k];
                            par[i] = k;
                        }
                    }
                }
            }
        }
        // print R[i]: R[par[i]] for all i
        for (int i = 0; i <= N; i++) {
            cout << R[N - i] << ": " << R[par[i]] << endl;
        }
        for (int i = 0; i <= N; i++) {
            cout << R[N - i] << ": " << dp[i] << endl;
        }
    }

    return 0;
}