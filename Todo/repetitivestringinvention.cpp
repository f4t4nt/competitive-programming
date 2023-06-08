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

// https://open.kattis.com/problems/repetitivestringinvention

vector<ll> MODS = {(ll) 1e9 - 1, (ll) 1e9};
ll cnt = sz(MODS);
constexpr ll BASE = 27;
vector<vector<ll>> powb(cnt, vector<ll>(1e3));

// s1 == (s2 - s3)?
bool is_prefix(
    vector<ll> &hash1,
    ll len1,
    vector<ll> &hash2,
    ll len2,
    vector<ll> &hash3
) {
    FOR (i, cnt) {
        if ((hash1[i] * powb[i][len2 - len1] + hash3[i]) % MODS[i] != hash2[i]) {
            return false;
        }
    }
    return true;
}

ll solve(str &s, ll del = 0) {
    ll n = sz(s);
    vector<vector<ll>> prefix(cnt, vector<ll>(n + 1));
    FOR (i, cnt) {
        FOR (j, n) {
            prefix[i][j + 1] = (prefix[i][j] * BASE + s[j] - 'a' + 1) % MODS[i];
        }
    }
    // [hash, length] -> [idk, cnt]
    map<pair<vector<ll>, ll>, map<ll, ll>> ref;
    // [i, j)
    vector<vector<vector<ll>>> range(n + 1, vector<vector<ll>>(n + 1, vector<ll>(cnt)));
    FOR (i, n) {
        FOB (j, i + 1, n + 1) {
            FOR (k, cnt) {
                range[i][j][k] = ((prefix[k][j] - prefix[k][i] * powb[k][j - i]) % MODS[k] + MODS[k]) % MODS[k];
            }
            ref[{range[i][j], j - i}][i] = ref[{range[i][j], j - i}].size() + 1;
        }
    }
    ll rv = 0;
    FOR (i, n) {
        FOB (j, i + 1, n + 1) {
            // 2 * (j - k) <= (j - i)
            // (i + j) / 2 <= k <= j
            FOB (k, (i + j + 1) / 2, j + 1 - del) {
                //                  [hash1]
                // [hash1?] [hash3]
                // [     hash2    ]
                // [         hashf       ]
                // vector<ll> hashf = range[i][j];
                vector<ll> hash1 = range[k][j],
                            hash2 = range[i][k],
                            hash3 = range[i + j - k][k];
                if (is_prefix(hash1, j - k, hash2, k - i, hash3)) {
                    // count how many times s[i + j - k, k) appears at idx >= j
                    // ll cnt0 = ref2[{hash3, k - (i + j - k)}][j];
                    ll tmp0 = ref[{hash3, k - (i + j - k)}].size();
                    auto it = ref[{hash3, k - (i + j - k)}].upper_bound(j - 1);
                    ll tmp1 = tmp0;
                    if (it != ref[{hash3, k - (i + j - k)}].end()) {
                        tmp1 = it->second - 1;
                    }
                    ll cnt = tmp0 - tmp1;
                    rv += cnt;
                }
            }
        }
    }
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    FOR (i, cnt) {
        powb[i][0] = 1;
        FOB (j, 1, 1e3) {
            powb[i][j] = (powb[i][j - 1] * BASE) % MODS[i];
        }
    }

    str s;
    cin >> s;
    ll rv = solve(s);
    flip(s);
    rv += solve(s, 1);
    cout << rv << '\n';

    return 0;
}