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

    str alphabet, s, subseq;
    vector<ll> char_ref(26, -1);
    cin >> alphabet >> s;
    FOR (i, sz(alphabet)) {
        char_ref[alphabet[i] - 'a'] = i;
    }
    vector<bool> used(sz(alphabet));
    vector<ll> used_chars;
    FOR (i, sz(s)) {
        if (!used[char_ref[s[i] - 'a']]) {
            used[char_ref[s[i] - 'a']] = true;
            used_chars.pb(char_ref[s[i] - 'a']);
        }
        if (sz(used_chars) == sz(alphabet)) {
            subseq.pb(s[i]);
            used_chars.clear();
            used = vector<bool>(sz(alphabet));
        }
    }

    FOR (i, sz(alphabet)) {
        if (!used[i]) {
            subseq.pb(alphabet[i]);
            break;
        }
    }

    vector<vector<ll>> ref(sz(s), vector<ll>(sz(alphabet), sz(s)));

    FORR (i, sz(s)) {
        if (i != sz(s) - 1) {
            ref[i] = ref[i + 1];
        }
        ref[i][char_ref[s[i] - 'a']] = i;
    }

    ll t;
    cin >> t;
    while (t--) {
        str q;
        cin >> q;
        if (sz(q) != sz(subseq)) {
            cout << 0 << '\n';
        } else {
            ll i = 0, j = 0;
            while (i < sz(s) && j < sz(q)) {
                if (ref[i][char_ref[q[j] - 'a']] == sz(s)) {
                    break;
                }
                i = ref[i][char_ref[q[j] - 'a']] + 1;
                j++;
            }
            cout << (j == sz(q) ? 0 : 1) << '\n';
        }
    }

    return 0;
}