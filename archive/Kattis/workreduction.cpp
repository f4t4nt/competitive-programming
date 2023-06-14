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
#define FOB(x, b, e) for(auto x = b; x != e; x++)
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

struct Agency {
    str name;
    ll a = 0, b = 0, val = 0;
    Agency(str line, ll &n, ll &m) {
        FORE (x, line) if (x == ':' or x == ',') x = ' ';
        stringstream ss(line);
        ss >> name >> a >> b;
        eval(n, m);
    }
    void eval(ll n, ll m) {
        val = 0;
        // largest x s.t. a * (x / 2) < b
        // x < 2 * b / a
        while (n / 2 >= m && (n + 1) / 2 * a > b) {
            val += b;
            n /= 2;
        }
        if (n > m) val += (n - m) * a;
    }
    bool operator<(const Agency &other) const {
        return (val < other.val || (val == other.val && name < other.name));
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll q;
    cin >> q;
    FOR (t, q) {
        ll n, m, l;
        cin >> n >> m >> l;
        vector<Agency> agencies;
        FOR (i, l) {
            str line;
            cin >> line;
            agencies.pb(Agency(line, n, m));
        }
        sort(all(agencies));
        cout << "Case " << t + 1 << '\n';
        FORE (agency, agencies) {
            cout << agency.name << ' ' << agency.val << '\n';
        }
    }

    return 0;
}