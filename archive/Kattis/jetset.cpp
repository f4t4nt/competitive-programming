#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    vector<pair<ll, ll>> waypoints(n);
    FOR (i, n) {
        cin >> waypoints[i].first >> waypoints[i].second;
    }

    bool pole = false;
    FOR (i, n) {
        if (abs(waypoints[i].second - waypoints[(i + 1) % n].second) == 180) {
            pole = true;
            break;
        }
    }
    if (pole) {
        cout << "yes\n";
        return 0;
    }

    vector<bool> visited(720);
    FOR (i, n) {
        waypoints[i].second += 180;
        waypoints[i].second *= 2;
    }

    FOR (i, n) {
        ll a = waypoints[i].second, b = waypoints[(i + 1) % n].second;
        if (a > b) {
            swap(a, b);
        }
        if (b - a < 720 - b + a) {
            FOB (x, a, b + 1) {
                visited[x] = true;
            }
        } else {
            FOB (x, b, 720) {
                visited[x] = true;
            }
            FOR (x, a + 1) {
                visited[x] = true;
            }
        }
    }

    ld rv = -1;
    FOR (i, 720) {
        if (!visited[i]) {
            rv = i;
        }
    }

    if (rv == -1) {
        cout << "yes\n";
    } else {
        rv /= 2.0;
        rv -= 180.0;
        cout << "no " << rv << '\n';
    }

    return 0;
}