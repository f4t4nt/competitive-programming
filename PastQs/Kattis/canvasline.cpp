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

int main() {
    ll n;
    cin >> n;

    vector<pair<ll, ll>> nums;
    FOR(i, n) {
        ll a, b;
        cin >> a >> b;
        nums.push_back({a, b});
    }

    ssort(nums);

    ll p;
    cin >> p;
    vector<ll> pegs(p + 1);
    FOR(i, p) {
        cin >> pegs[i];
    }
    pegs.push_back(1e9+7);

    ll p_idx = 0;
    vector<ll> used(n), rv;
    FOR(i, n) {
        auto cur = nums[i];
        while (p_idx < p && pegs[p_idx] <= cur.second)  {
            if (pegs[p_idx] >= cur.first) {
                used[i]++;
            }
            p_idx++;
        }
        if (used[i] >= 3) {
            cout << "impossible";
            return 0;
        }
        if (p_idx > 0) p_idx--;
    }

    p_idx = 0;

    FOR(i, n) {
        auto cur = nums[i];
        while (p_idx < p && pegs[p_idx] <= cur.second)  {
            p_idx++;
        }
        bool last = false;
        if (p_idx > 0 && pegs[p_idx - 1] == cur.second) {
            last = true;
        }
        if (used[i] == 0) {
            rv.push_back(cur.second - 1);
            if (i != n - 1 && nums[i + 1].first == cur.second) {
                if (used[i + 1] == 2) {
                    rv.push_back(cur.second - 2);
                }
                else {
                    rv.push_back(cur.second);
                    used[i + 1]++;
                }
            }
            else {
                rv.push_back(cur.second);
            }
            used[i] = 2;
        }
        elif (used[i] == 1) {
            if (last) {
                rv.push_back(cur.second - 1);
            }
            else {
                if (i != n - 1 && nums[i + 1].first == cur.second) {
                    if (used[i + 1] == 2) {
                        if (pegs[p_idx - 1] != (cur.first + cur.second) / 2) {
                            rv.push_back((cur.first + cur.second) / 2);
                        }
                        else {
                            rv.push_back((cur.first + cur.second) / 2 + 1);
                        }
                    }
                    else {
                        rv.push_back(cur.second);
                        used[i + 1]++;
                    }
                }
                else {
                    rv.push_back(cur.second);
                }
            }
            used[i] = 2;
        }
    }

    ssort(rv);
    cout << rv.size() << endl;
    FORE(x, rv) {
        cout << x << ' ';
    }

    return 0;
}