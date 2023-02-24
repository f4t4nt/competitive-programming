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

struct Resident {
    str name;
    ll party;
    vector<ll> clubs;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    str line;
    getline(cin, line);
    ll t = stoll(line);

    while (t--) {
        map<str, ll> party_map, club_map;

        getline(cin, line);
        ll n = stoll(line);
        getline(cin, line);
        vector<Resident> residents(n);
        FOR (i, n) {
            istringstream iss(line);
            str party;
            iss >> residents[i].name >> party;
            if (party_map.find(party) == party_map.end()) {
                party_map[party] = sz(party_map);
            }
            residents[i].party = party_map[party];
            ll club_count;
            iss >> club_count;
            FOR (j, club_count) {
                str club;
                iss >> club;
                if (club_map.find(club) == club_map.end()) {
                    club_map[club] = sz(club_map);
                }
                residents[i].clubs.pb(club_map[club]);
            }
        }
    }

    return 0;
}