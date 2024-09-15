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
#define FOB(x, b, e) for (auto x = b; x < e; x++)
#define FORE(x, C) for (auto &x : C)

// #ifdef LOCAL
// #include "tester.cpp"
// #define main test_main
// extern istringstream fin;
// extern ostringstream fout;
// string test_file_name = "tests";
// #define cin fin
// #define cout fout
// #endif

const bool PRUNE = true;
const bool PREFIX = true;
const bool HINT = true;
const ll ALPHA = 26;
const str SRC_FILE = "ubuntu.csv";
const str FREQ_FILE = "freqs.csv";

struct Trie {
    ch c;
    str best = "", prefix = "";
    ld prob, win_prob = 0;
    bool ending = false;
    vector<Trie*> children = vector<Trie*>(ALPHA, nullptr);

    Trie(ch c, ld prob, str prefix = "") : c(c), prob(prob), prefix(prefix) {}

    void insert(ll i, str &word, ld p) {
        this->prob = max(this->prob, p);
        if (i == sz(word)) {
            ending = i > 3;
            return;
        }
        ll si = word[i] - 'a';
        if (children[si] == nullptr) {
            if (sz(word) <= 3 && PRUNE) { // avoid words like "nus", prefix of no other word
                return;
            }
            if (PREFIX) {
                children[si] = new Trie(word[i], p, prefix + word[i]);
            } else {
                children[si] = new Trie(word[i], p);
            }
        }
        children[si]->insert(i + 1, word, p);
    }

    void print() {
        cout << c << " " << prob << " " << win_prob << " " << best;
        if (ending) {
            cout << " END";
        }
        cout << endl;
    }
};

ld game(Trie *cur, bool alice, str word = "") {
    ld res = 0;
    FOR (i, ALPHA) if (cur->children[i] != nullptr) {
        // probability i win if i pick this letter * probability i know this prefix
        ld prob = (1 - game(cur->children[i], !alice, word + cur->children[i]->c)) * cur->children[i]->prob;
        if (cur->children[i]->ending) {
            // if this is a word, probability other player doesn't notice
            prob *= (1 - cur->children[i]->prob);
        }
        if (prob > res) {
            res = prob;
            cur->best = cur->children[i]->c;
        } elif (prob == res) {
            cur->best += cur->children[i]->c;
        }
    }
    cur->win_prob = res;
    return res;
}

ld qry(map<str, ld> &probs, str word) {
    return probs[word];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    map<str, ll> freqs;
    ifstream fin(FREQ_FILE);
    str line;
    getline(fin, line);
    ld MAX_CNT = 0;

    auto to_lower = [](str &s) {
        transform(all(s), s.begin(), ::tolower);
        FORE (c, s) if (c < 'a' || c > 'z')
            s.erase(remove(all(s), c), s.end());
    };

    while (getline(fin, line)) {
        str word;
        ld count;
        stringstream ss(line);
        getline(ss, word, ',');
        to_lower(word);
        ss >> count;
        freqs[word] = count;
        MAX_CNT = max(MAX_CNT, count);
    }

    map<str, ld> probs;
    vector<pair<str, ld>> words;
    fin = ifstream(SRC_FILE);
    getline(fin, line);

    while (getline(fin, line)) {
        str word;
        ld prob;
        stringstream ss(line);
        ss >> word;
        if (word.find_first_not_of("abcdefghijklmnopqrstuvwxyz") != str::npos) {
            continue;
        }
        to_lower(word);
        prob = pow((freqs[word] + 1e3) / (MAX_CNT + 1e3), 0);
        words.pb({word, prob});
        probs[word] = prob;
    }

    sort(all(words), [](auto &a, auto &b) {
        return sz(a.f) > sz(b.f);
    });

    Trie *root = new Trie(' ', 1, "");
    for (auto [word, prob] : words) {
        root->insert(0, word, prob);
    }

    ld res = game(root, true);
    cout << "Alice's win probability: " << res << endl;
    cout << "Example sequence: ";
    auto it = root;
    while (it->best != "") {
        ch c = it->best[rng() % sz(it->best)];
        cout << c;
        it = it->children[c - 'a'];
    }
    cout << endl;

    // while (true) {
    //     str word;
    //     cin >> word;
    //     auto cur = root;
    //     FOR (i, sz(word)) {
    //         cur->print();
    //         cur = cur->children[word[i] - 'a'];
    //     }
    //     cur->print();
    // }

    while (true) {
        str input, word = "";
        auto cur = root;
        cin >> input;
        if (input == "exit") break;
        ch c;
        bool me = input != "alice";

        auto i_pick = [&]() {
            c = cur->best[rng() % sz(cur->best)];
            // c = "testing"[sz(word)];
            cout << "I pick: " << "(" << cur->best << ")" << endl << c << endl;
        };

        auto you_pick = [&]() {
            bool ok = false;
            while (!ok) {
                cout << "You pick:";
                if (HINT) {
                    cout << " (" << cur->best << ")";
                }
                cout << endl;
                cin >> c;
                if (cur->children[c - 'a'] == nullptr) {
                    cout << "Invalid prefix" << endl;
                } else {
                    ok = true;
                }
            }
        };

        while (!cur->ending) {
            me ? i_pick() : you_pick();
            word += c;
            cur = cur->children[c - 'a'];
            cout << "Word: " << word << endl;
            if (!cur->ending && cur->best == "") {
                cout << "No more picks" << endl;
                break;
            }
            me = !me;
        }

        cout << (me ? "I win!" : "You win!") << endl;
    }

    return 0;
}