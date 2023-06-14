#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using cd = complex<double>;
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

constexpr ll MOD = 1e9 + 7;
constexpr ll BASE = 8;
vector<ll> powb = {1};

ll get_hash(ll &len, str &s) {
    ll rv = 0;
    FOR (i, len) {
        rv = (rv * BASE) % MOD;
        if (i < sz(s)) {
            rv += s[i] - 'A' + 1;
        }
    }
    return rv;
}

void upd_hash(ll &len, ll &hash, ll rem, ll ins) {
    hash = ((hash * BASE - rem * powb[len] + ins) % MOD + MOD) % MOD;
}

multiset<ll> get_hashes(ll &len, str &s) {
    ll hash = get_hash(len, s);
    multiset<ll> rv = {hash};
    FOR (i, sz(s) - 1) {
        ll c = (i + len < sz(s) ? s[i + len] - 'A' + 1 : 0);
        upd_hash(len, hash, s[i] - 'A' + 1, c);
        rv.insert(hash);
    }
    return rv;
}

bool valid(ll mid, str &s, vector<str> &ref) {
    multiset<ll> hashes = get_hashes(mid, s);
    FORE (r, ref) {
        multiset<ll> rem = get_hashes(mid, r);
        FORE (hash, rem) {
            hashes.erase(hash);
            // if (sz(hashes) * 2 < sz(s)) {
            //     return false;
            // }
        }
    }
    // return true;
    return sz(hashes) * 2 >= sz(s);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    FOR (i, 1e3 + 1) {
        powb.pb((powb.back() * BASE) % MOD);
    }

    ll n, m;
    cin >> n >> m;
    str s;
    cin >> s;
    m--;
    vector<str> ref(m);
    FOR (i, m) {
        cin >> ref[i];
    }

    if (!valid(n, s, ref)) {
        cout << -1 << '\n';
        return 0;
    }

    ll lo = 1, hi = n;
    while (lo < hi) {
        ll mid = (lo + hi) / 2;
        if (valid(mid, s, ref)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    cout << lo << '\n';

    return 0;
}