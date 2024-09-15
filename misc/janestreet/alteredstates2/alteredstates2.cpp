#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef complex<long double> cd;
typedef long double ld;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

using indexed_set = tree<
    pld,
    null_type,
    less<pld>,
    rb_tree_tag,
    tree_order_statistics_node_update>;

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
#define f first
#define s second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)

// #ifdef LOCAL
// #include "tester.cpp"
// #define main test_main
// extern istringstream fin;
// extern ostringstream fout;
// string test_file_name = "tests";
// #define cin fin
// #define cout fout
// #endif

map<str, ll> state_populations = {
    {"California", 39538223},
    {"Texas", 29145505},
    {"Florida", 21538187},
    {"New York", 20201249},
    {"Pennsylvania", 13002700},
    {"Illinois", 12812508},
    {"Ohio", 11799448},
    {"Georgia", 10711908},
    {"North Carolina", 10439388},
    {"Michigan", 10077331},
    {"New Jersey", 9288994},
    {"Virginia", 8631393},
    {"Washington", 7705281},
    {"Arizona", 7151502},
    {"Massachusetts", 7029917},
    {"Tennessee", 6910840},
    {"Indiana", 6785528},
    {"Maryland", 6177224},
    {"Missouri", 6154913},
    {"Wisconsin", 5893718},
    {"Colorado", 5773714},
    {"Minnesota", 5706494},
    {"South Carolina", 5118425},
    {"Alabama", 5024279},
    {"Louisiana", 4657757},
    {"Kentucky", 4505836},
    {"Oregon", 4237256},
    {"Oklahoma", 3959353},
    {"Connecticut", 3605944},
    {"Utah", 3271616},
    {"Iowa", 3190369},
    {"Nevada", 3104614},
    {"Arkansas", 3011524},
    {"Mississippi", 2961279},
    {"Kansas", 2937880},
    {"New Mexico", 2117522},
    {"Nebraska", 1961504},
    {"Idaho", 1839106},
    {"West Virginia", 1793716},
    {"Hawaii", 1455271},
    {"New Hampshire", 1377529},
    {"Maine", 1362359},
    {"Rhode Island", 1097379},
    {"Montana", 1084225},
    {"Delaware", 989948},
    {"South Dakota", 886667},
    {"North Dakota", 779094},
    {"Alaska", 733391},
    {"District of Columbia", 689545},
    {"Vermont", 643077},
    {"Wyoming", 576851}
};

const ll TARGET = 165379868;
const ll DIM = 5;

ll dx[] = {0, 0, 1, -1, 1, -1, 1, -1};
ll dy[] = {1, -1, 0, 0, 1, -1, -1, 1};

pair<ll, set<str>> get_score(vector<str> &grid) {
    assert(sz(grid) == DIM && sz(grid[0]) == DIM);
    set<str> used;
    ll score = 0;
    FOR (i, DIM) FOR (j, DIM) {
        for (auto &[st, p] : state_populations) {
            if (used.count(st)) {
                continue;
            }
            queue<tuple<ll, ll, ll, ll>> q;
            q.push({i, j, 0, 0});
            bool ok = false;
            while (!q.empty()) {
                auto [x, y, idx, penalty] = q.front();
                q.pop();
                if (idx == sz(st)) {
                    ok = true;
                    break;
                }
                if (x < 0 || x >= DIM || y < 0 || y >= DIM) {
                    continue;
                }
                if (grid[x][y] != st[idx]) {
                    penalty++;
                }
                if (penalty > 1) {
                    continue;
                }
                FOR (d, 8) {
                    q.push({x + dx[d], y + dy[d], idx + 1, penalty});
                }
            }
            if (ok) {
                score += p;
                used.insert(st);
            }
        }
    }
    return {score, used};
}

pair<ll, vector<str>> insert_word(vector<str> &grid, str &st, ll x, ll y, ll idx, ll penalty, ll &lim, ll penalty_lim) {
    if (lim-- <= 0) {
        return {0, grid};
    }

    if (idx == sz(st)) {
        return {get_score(grid).f, grid};
    }

    vector<str> new_grid = grid;
    // pair<ll, vector<str>> res = {get_score(grid).f, grid};
    pair<ll, vector<str>> res = {0, grid};
    if (x < 0 || x >= DIM || y < 0 || y >= DIM) {
        return res;
    }

    ll offset = rng() % 8;

    if (grid[x][y] != st[idx] && grid[x][y] != ' ') {
        FOR (d, 8) {
            res = max(res, insert_word(grid, st, x + dx[(d + offset) % 8], y + dy[(d + offset) % 8], idx + 1, penalty + 1, lim, penalty_lim));
        }
        penalty++;
    }

    if (penalty > penalty_lim) {
        return res;
    }

    offset = rng() % 8;
    new_grid[x][y] = st[idx];
    FOR (d, 8) {
        res = max(res, insert_word(new_grid, st, x + dx[(d + offset) % 8], y + dy[(d+ offset) % 8], idx + 1, penalty, lim, penalty_lim));
    }

    return res;
}

void print_grid(vector<str> &grid) {
    FOR (i, DIM) {
        cout << grid[i] << endl;
    }
    cout << endl;
    FOR (i, DIM) {
        cout << grid[i];
    }
    auto [score, used] = get_score(grid);
    cout << " " << score << (score >= TARGET ? " OK" : "") << endl << sz(used) << endl;
    for (auto &st : used) {
        cout << st << " ";
    }
    cout << endl;
}

vector<str> find_word(vector<str> grid, str &st) {
    queue<tuple<ll, ll, ll, ll, set<pll>>> q;
    FOR (i, DIM) FOR (j, DIM) {
        if (grid[i][j] == st[0]) {
            q.push({i, j, 0, 0, {{i, j}}});
        } else {
            q.push({i, j, 0, 1, {{i, j}}});
        }
    }
    bool ok = false;
    while (!q.empty()) {
        auto [x, y, idx, penalty, used] = q.front();
        used.insert({x, y});
        q.pop();
        if (idx == sz(st)) {
            ok = true;
            for (auto [i, j] : used) {
                grid[i][j] = tolower(grid[i][j]);
            }
            break;
        }
        if (x < 0 || x >= DIM || y < 0 || y >= DIM) {
            continue;
        }
        if (grid[x][y] != st[idx]) {
            penalty++;
        }
        if (penalty > 1) {
            continue;
        }
        FOR (d, 8) {
            q.push({x + dx[d], y + dy[d], idx + 1, penalty, used});
        }
    }
    if (!ok) {
        cout << st << " not found" << endl;
        return grid;
    }
    return grid;
}

// CRNITIOASEFLIMNNAYERIDWOS 200310617 OK
// 21
// ALABAMA ALASKA ARIZONA ARKANSAS CALIFORNIA COLORADO FLORIDA IDAHO ILLINOIS INDIANA IOWA KANSAS LOUISIANA MAINE MARYLAND NEVADA NEWJERSEY NEWYORK OHIO OREGON TEXAS 

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    map<str, ll> tmp = state_populations;
    state_populations.clear();
    for (auto &[st, p] : tmp) {
        str new_key;
        for (auto c : st) {
            if (c == ' ') {
                continue;
            }
            new_key += toupper(c);
        }
        state_populations[new_key] = p;
    }

    // vector<str> grid = {"THO", "AIN", "ESL"};
    // auto [score, used] = get_score(grid);
    // cout << score << '\n';
    // for (auto &st : used) {
    //     cout << st << '\n';
    // }
    // return 0;

    vector<str> grid(DIM, str(DIM, ' '));
    vector<pll> pos;
    FOR (i, DIM) FOR (j, DIM) {
        pos.pb({i, j});
    }

    while (true) {
        str cmd; cin >> cmd;
        if (cmd == "set") {
            str unwrapped;
            // get the whole next line, make sure to avoid wonky behavior
            cin.ignore();
            getline(cin, unwrapped);
            while (sz(unwrapped) < DIM * DIM) {
                unwrapped += ' ';
            }
            FOR (i, DIM) FOR (j, DIM) {
                grid[i][j] = unwrapped[i * DIM + j];
            }
            print_grid(grid);
        } elif (cmd == "insert") {
            str st; cin >> st;
            ll lim, penalty_lim; cin >> lim >> penalty_lim;
            for (auto &c : st) {
                c = toupper(c);
            }
            // if (!state_populations.count(st)) {
            //     cout << "Invalid state" << endl;
            //     continue;
            // }
            pair<ll, vector<str>> res = {0, grid};
            shuffle(all(pos), rng);
            for (auto [x, y] : pos) {
                res = max(res, insert_word(grid, st, x, y, 0, 0, lim, penalty_lim));
            }
            grid = res.s;
            print_grid(grid);
        } elif (cmd == "print") {
            print_grid(grid);
        } elif (cmd == "exit") {
            break;
        } elif (cmd == "eval") {
            while (true) {
                str st; cin >> st;
                if (st == "exit") {
                    break;
                }
                for (auto &c : st) {
                    c = toupper(c);
                }
                auto tmp = find_word(grid, st);
                print_grid(tmp);
            }
        } else {
            cout << "Invalid command" << endl;
        }
    }

    return 0;
}