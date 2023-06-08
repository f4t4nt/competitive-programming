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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll T;
    cin >> T;
    while (T--) {
        vector<str> s(2);
        cin >> s[0] >> s[1];
        ll n = sz(s[0]), cnt = 0, t, q;
        cin >> t >> q;
        FOR (i, n) {
            cnt += s[0][i] == s[1][i];
        }
        // time to unblock, idx to unblock
        priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<>> pq;
        FOR (cur_t, q) {
            while (!pq.empty() && pq.top().first <= cur_t) {
                auto [t, idx] = pq.top();
                pq.pop();
                s[0][idx] = 'a' + s[0][idx] - 'A';
                s[1][idx] = 'a' + s[1][idx] - 'A';
                if (s[0][idx] != s[1][idx]) {
                    cnt--;
                }
            }
            ll q_type;
            cin >> q_type;
            if (q_type == 1) {
                ll pos;
                cin >> pos;
                pos--;
                s[0][pos] = 'A' + s[0][pos] - 'a';
                s[1][pos] = 'A' + s[1][pos] - 'a';
                if (s[0][pos] != s[1][pos]) {
                    cnt++;
                }
                pq.push({cur_t + t, pos});
            } elif (q_type == 2) {
                ll sidx1, pos1, sidx2, pos2;
                cin >> sidx1 >> pos1 >> sidx2 >> pos2;
                sidx1--, pos1--, sidx2--, pos2--;
                cnt -= (s[0][pos1] == s[1][pos1]) + (s[0][pos2] == s[1][pos2]);
                swap(s[sidx1][pos1], s[sidx2][pos2]);
                cnt += (s[0][pos1] == s[1][pos1]) + (s[0][pos2] == s[1][pos2]);
            } else {
                cout << (cnt == n ? "YES" : "NO") << '\n';
            }
        }
    }

    return 0;
}