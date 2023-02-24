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

ll moore(ll speed, vector<pair<ll, ll>> &tasks) {
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, 
        function<bool(pair<ll, ll>, pair<ll, ll>)>> pq(
            [](pair<ll, ll> a, pair<ll, ll> b) {
                return a.second < b.second;
            }
        );
    ll rv = 0;
    ld time = 0;
    FORE (task, tasks) {
        pq.push(task);
        ld task_time = (ld) task.second / speed;
        time += task_time;
        if (time > task.first && abs(time - task.first) >= 5e-15) {
            pair<ll, ll> worst = pq.top();
            pq.pop();
            time -= (ld) worst.second / speed;
            rv++;
        }
    }
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);   
    cout.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    vector<pair<ll, ll>> tasks(n);
    FOR (i, n) {
        cin >> tasks[i].second >> tasks[i].first;
    }
    ssort(tasks);

    ll lo = 1, hi = LLONG_MAX;
    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;
        if (moore(mid, tasks) <= m) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    cout << lo << '\n';

    return 0;
}