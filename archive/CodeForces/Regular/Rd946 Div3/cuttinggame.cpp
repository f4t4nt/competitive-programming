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
#define f first
#define s second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)
#define FOB(x, b, e) for (auto x = b; x < e; x++)
#define FORE(x, C) for (auto &x : C)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

struct Chip {
    ll val, x, y;
    Chip(ll x, ll y) : val(1), x(x), y(y) {}

    ll pop() {
        ll ret = val;
        val = 0;
        return ret;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll a, b, n, m;
        cin >> a >> b >> n >> m;
        vector<Chip> chips;
        vector<ll> xchips, ychips;
        FOR (i, n) {
            ll x, y; cin >> x >> y;
            chips.pb(Chip(x, y));
            // xchips.pb(&chips[i]);
            // ychips.pb(&chips[i]);
            xchips.pb(i);
            ychips.pb(i);
        }
        // sort(all(xchips), [](Chip* a, Chip* b) { return a->x < b->x; });
        // sort(all(ychips), [](Chip* a, Chip* b) { return a->y < b->y; });
        sort(all(xchips), [&](ll a, ll b) { return chips[a].x < chips[b].x; });
        sort(all(ychips), [&](ll a, ll b) { return chips[a].y < chips[b].y; });

        // deque<Chip*> xq, yq;
        deque<ll> xq, yq;
        FOR (i, n) {
            // xq.pb(xchips[i]);
            // yq.pb(ychips[i]);
            xq.pb(xchips[i]);
            yq.pb(ychips[i]);
        }

        ll mnx = 0, mny = 0, mxx = a + 1, mxy = b + 1;
        ll scores[2] = {0};
        FOR (i, m) {
            ch dir; cin >> dir;
            ll amt; cin >> amt;
            if (dir == 'D') mxx -= amt;
            elif (dir == 'U') mnx += amt;
            elif (dir == 'R') mxy -= amt;
            elif (dir == 'L') mny += amt;

            // while (!xq.empty() && xq.front()->x <= mnx) {
            //     scores[i % 2] += xq.front()->pop();
            //     xq.pop_front();
            // }
            // while (!xq.empty() && xq.back()->x >= mxx) {
            //     scores[i % 2] += xq.back()->pop();
            //     xq.pop_back();
            // }
            // while (!yq.empty() && yq.front()->y <= mny) {
            //     scores[i % 2] += yq.front()->pop();
            //     yq.pop_front();
            // }
            // while (!yq.empty() && yq.back()->y >= mxy) {
            //     scores[i % 2] += yq.back()->pop();
            //     yq.pop_back();
            // }

            while (!xq.empty() && chips[xq.front()].x <= mnx) {
                scores[i % 2] += chips[xq.front()].pop();
                xq.pop_front();
            }
            while (!xq.empty() && chips[xq.back()].x >= mxx) {
                scores[i % 2] += chips[xq.back()].pop();
                xq.pop_back();
            }
            while (!yq.empty() && chips[yq.front()].y <= mny) {
                scores[i % 2] += chips[yq.front()].pop();
                yq.pop_front();
            }
            while (!yq.empty() && chips[yq.back()].y >= mxy) {
                scores[i % 2] += chips[yq.back()].pop();
                yq.pop_back();
            }
        }
        cout << scores[0] << ' ' << scores[1] << '\n';
    }

    return 0;
}