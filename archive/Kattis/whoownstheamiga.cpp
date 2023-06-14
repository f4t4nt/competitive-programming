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

// https://open.kattis.com/problems/amiga

str obj[] = {
    "1", "2", "3", "4", "5",
    "blue", "green", "red", "white", "yellow",
    "anna", "bernhard", "chris", "david", "ellen",
    "danish", "finnish", "icelandic", "norwegian", "swedish",
    "amiga", "atari", "linux", "mac", "windows",
    "c", "c++", "java", "pascal", "perl"
};
str rel[] = {"same-as", "left-of", "right-of", "next-to"};
constexpr bool ASSERT = true;

bool valid(vector<ll> &pos, vector<tuple<ll, ll, ll>> &rels) {
    FORE (rel, rels) {
        ll o1, r, o2;
        tie(o1, r, o2) = rel;
        if (pos[o1] == -1 || pos[o2] == -1) {
            continue;
        } elif (r == 0) {
            if (pos[o1] != pos[o2]) {
                if (ASSERT) assert(false);
                return false;
            }
        } elif (r == 1) {
            if (pos[o1] != pos[o2] - 1) {
                if (ASSERT) assert(false);
                return false;
            }
        } elif (r == 2) {
            if (pos[o1] != pos[o2] + 1) {
                if (ASSERT) assert(false);
                return false;
            }
        } elif (r == 3) {
            if (abs(pos[o1] - pos[o2]) != 1) {
                if (ASSERT) assert(false);
                return false;
            }
        }
    }
    return true;
}

vector<vector<str>> conv(vector<ll> &pos) {
    vector<vector<str>> rv(5);
    FOR (i, 30) {
        if (pos[i] != -1) {
            rv[pos[i]].pb(obj[i]);
        }
    }
    return rv;
}

void dfs(
    ll obj_i,
    vector<ll> &pos,
    vector<ll> &ord,
    vector<tuple<ll, ll, ll>> &rels,
    map<str, ll> &obj_m,
    vector<vector<ll>> &rel_idxs,
    set<str> &rv
) {
    ll i = ord[obj_i];
    if (obj_i == 30 || (sz(rel_idxs[i]) == 0 && i >= 5)) {
        if (ASSERT) assert(valid(pos, rels));
        if (valid(pos, rels)) {
            ll amiga_pos = pos[obj_m["amiga"]];
            if (amiga_pos != -1) {
                bool add = false;
                set<str> unset;
                FOB (i, 10, 15) {
                    if (pos[i] == amiga_pos) {
                        add = true;
                        rv.insert(obj[i]);
                    }
                    if (pos[i] == -1) {
                        unset.insert(obj[i]);
                    }
                }
                if (!add) {
                    FORE (o, unset) {
                        rv.insert(o);
                    }
                }
                return;
            } else {
                bool ok = true;
                FOB (j, 20, 25) {
                    ok &= pos[j] != -1;
                }
                if (ok) {
                    set<str> unset;
                    FOB (i, 10, 15) {
                        if (pos[i] == -1) {
                            unset.insert(obj[i]);
                        }
                    }
                    if (sz(unset) == 1) {
                        FORE (o, unset) {
                            rv.insert(o);
                        }
                        return;
                    }
                }
            }
        }
    }
    if (ASSERT) assert(pos[i] == -1);
    set<ll> pos_set;
    if (i < 5) {
        pos_set = {i};
    } else {
        pos_set = {0, 1, 2, 3, 4};
        ll obj_t = i / 5;
        FOR (j, 5) {
            pos_set.erase(pos[j + obj_t * 5]);
        }
        FORE (rel_idx, rel_idxs[i]) {
            ll o1, r, o2;
            tie(o1, r, o2) = rels[rel_idx];
            if (o1 != i) {
                swap(o1, o2);
                if (r == 1) {
                    r = 2;
                } elif (r == 2) {
                    r = 1;
                }
            }
            str obj1 = obj[o1], obj2 = obj[o2], rel0 = rel[r];
            ll &pos2 = pos[o2];
            if (pos2 != -1) {
                if (r == 0) {
                    if (pos_set.count(pos2) == 0) {
                        return;
                    } else {
                        pos_set = {pos2};
                    }
                } elif (r == 1) {
                    if (pos_set.count(pos2 - 1) == 0) {
                        return;
                    } else {
                        pos_set = {pos2 - 1};
                    }
                } elif (r == 2) {
                    if (pos_set.count(pos2 + 1) == 0) {
                        return;
                    } else {
                        pos_set = {pos2 + 1};
                    }
                } elif (r == 3) {
                    if (pos_set.count(pos2 - 1) == 0 && pos_set.count(pos2 + 1) == 0) {
                        return;
                    } else {
                        if (pos_set.count(pos2 - 1) == 0) {
                            pos_set = {pos2 + 1};
                        } elif (pos_set.count(pos2 + 1) == 0) {
                            pos_set = {pos2 - 1};
                        } else {
                            pos_set = {pos2 - 1, pos2 + 1};
                        }
                    }
                }
            }
        }
    }
    FORE (p, pos_set) {
        pos[i] = p;
        dfs(obj_i + 1, pos, ord, rels, obj_m, rel_idxs, rv);
        pos[i] = -1;
        if (sz(rv) > 1) {
            return;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    map<str, ll> obj_m, rel_m;
    FOR (i, 30) obj_m[obj[i]] = i;
    FOR (i, 4) rel_m[rel[i]] = i;

    ll T;
    cin >> T;
    for (ll t = 1; t <= T; t++) {
        ll n;
        cin >> n;
        vector<pair<ll, ll>> cnts;
        FOR (i, 30) {
            if (i < 5) {
                cnts.pb({100, i});
            } else {
                cnts.pb({0, i});
            }
        }
        vector<tuple<ll, ll, ll>> rels(n);
        vector<vector<ll>> rel_idxs(30);
        FOR (i, n) {
            str o1, r, o2;
            cin >> o1 >> r >> o2;
            rels[i] = {obj_m[o1], rel_m[r], obj_m[o2]};
            cnts[obj_m[o1]].first++;
            cnts[obj_m[o2]].first++;
            rel_idxs[obj_m[o1]].pb(i);
            rel_idxs[obj_m[o2]].pb(i);
        }
        rsort(cnts);
        vector<ll> ord(30);
        FOR (i, 30) ord[i] = cnts[i].second;
        set<str> rv;
        vector<ll> pos(30, -1);
        dfs(0, pos, ord, rels, obj_m, rel_idxs, rv);
        cout << "scenario #" << t << ": ";
        if (sz(rv) == 0) {
            cout << "impossible.\n";
        } elif (sz(rv) == 1) {
            cout << *rv.begin() << " owns the amiga.\n";
        } else {
            cout << "cannot identify the amiga owner.\n";
        }
    }

    return 0;
}