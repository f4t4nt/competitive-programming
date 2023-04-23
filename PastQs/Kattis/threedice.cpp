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

bool dfs(ll idx, vector<ll> &cnt, vector<ll> &ref, vector<str> &words) {
    if (idx == sz(words)) {
        return true;
    }

    vector<ll> perm = {0,1,2};
    str &word = words[idx];

    do {
        bool ok = true;
        set<ll> new_j;
        FOR (j, 3) {
            if (ref[word[j] - 'a'] == -1) {
                new_j.insert(j);
                ref[word[j] - 'a'] = perm[j];
                cnt[perm[j]]++;
                if (cnt[perm[j]] > 6) {
                    ok = false;
                    break;
                }
            } elif (ref[word[j] - 'a'] != perm[j]) {
                ok = false;
                break;
            }
        }
        if (ok && dfs(idx + 1, cnt, ref, words)) {
            return true;
        }
        FORE (j, new_j) {
            ref[word[j] - 'a'] = -1;
            cnt[perm[j]]--;
        }
    } while (next_permutation(all(perm)));

    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);   
    cout.tie(nullptr);

    ll n;
    cin >> n;
    vector<str> words(n);
    FOR (i, n) {
        cin >> words[i];
    }

    bool ok = true;
    FORE (word, words) {
        if (word[0] == word[1] ||
            word[0] == word[2] ||
            word[1] == word[2])
        {
            ok = false;
            break;
        }
    }

    if (!ok) {
        cout << 0 << '\n';
        return 0;
    }

    vector<ll> ref(26, -1), cnt(3, 1);
    FOR (j, 3) {
        ref[words[0][j] - 'a'] = j;
    }

    if (!dfs(1, cnt, ref, words)) {
        cout << 0 << '\n';
    } else {
        vector<str> rv(3);
        FOR (i, 26) {
            if (ref[i] != -1) {
                rv[ref[i]] += (ch) ('a' + i);
            }
        }
        FOR (j, 3) {
            FOR (i, 26) {
                if (sz(rv[j]) == 6) {
                    break;
                } elif (ref[i] == -1) {
                    ref[i] = j;
                    rv[j] += (ch) ('a' + i);
                }
            }
        }
        FOR (j, 3) {
            cout << rv[j] << ' ';
        }
        cout << '\n';
    }
    
    return 0;
}