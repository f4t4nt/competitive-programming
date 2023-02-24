#include <algorithm>
#include <cmath>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <list>
#include <map>
#include <math.h>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <string>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using ll = long long;
using ull = unsigned long long;
using vl = vector<ll>;
using vvl = vector<vl>;
using vvvl = vector<vvl>;
using vvvvl = vector<vvvl>;
using pll = pair<ll, ll>;
using vpll = vector<pll>;
using vvpll = vector<vpll>;
using plvpll = pair<ll, vpll>;
using plvl = pair<ll, vl>;
using vplvl = vector<plvl>;
using sl = set<ll>;
using spll = set<pll>;
using vsl = vector<sl>;
using ssl = set<sl>;
using plsl = pair<ll, sl>;
using vplsl = vector<plsl>;
using plspll = pair<ll, spll>;
using msl = multiset<ll>;
using mspll = multiset<pll>;
using vb = vector<bool>;
using vvb = vector<vb>;
using plvb = pair<ll, vb>;
using mll = map<ll, ll>;
using mlll = map<ll, mll>;
using mlvl = map<ll, vl>;
using mlpll = map<ll, pll>;
using mplll = map<pll, ll>;
using mlvpll = map<ll, vpll>;
using mlsl = map<ll, sl>;
using mpllb = map<pll, bool>;
using vmll = vector<mll>;
using ql = queue<ll>;
using qpll = queue<pll>;
using fl = long double;
using vf = vector<fl>;
using vvf = vector<vf>;
using str = string;
using vstr = vector<str>;
using mstrl = map<str, ll>;
using mcl = map<char, ll>;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define flip(C) reverse(C.begin(), C.end())
#define ssort(C) sort(C.begin(), C.end())
#define rsort(C) sort(C.begin(), C.end(), greater<>())
#define max_elem(C) *max_element(C.begin(), C.end())
#define min_elem(C) *min_element(C.begin(), C.end())
#define contains(C, x) find(C.begin(), C.end(), x) != C.end()

#define FOR(x, e) for(ll  x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = (ll) b; x != (ll) e; x++)
#define FOE(x, e, b) for(auto x = (ll) e - 1; x != (ll) b; x--)
#define FOI(x, e, i) for(ll x = 0; x < (ll) e; x += (ll) i)
#define FOBI(x, b, e, i) for(ll x = (ll) b; x < (ll) e; x += (ll) i)
#define FORE(x, C) for(auto &x : C)

// #ifdef LOCAL
// #include "tester.cpp"
// #define main test_main
// extern istringstream fin;
// extern ostringstream fout;
// string test_file_name = "tests";
// #define cin fin
// #define cout fout
// #endif

// https://leetcode.com/problems/word-search-ii/

vector<int> dx { -1, 0, 1, 0};
vector<int> dy { 0, -1, 0, 1};

bool recurse(vector<vector<char>>& board, vector<vector<bool>>& visited, string& word, int x0, int y0, int idx) {
    visited[x0][y0] = true;
    if (idx == word.size()) {
        return true;
    }
    for (int i = 0; i < 4; i++) {
        int x1 = x0 + dx[i], y1 = y0 + dy[i];
        if (0 <= x1 &&
            x1 < board.size() &&
            0 <= y1 &&
            y1 < board[0].size() &&
            !visited[x1][y1] &&
            board[x1][y1] == word[idx] &&
            recurse(board, visited, word, x1, y1, idx + 1)) {
                return true;
        }
    }
    visited[x0][y0] = false;
    return false;
}

bool valid(vector<vector<char>>& board, string word, map<char, vector<pair<int, int>>>& locations) {
    if(locations[word[0]].size() > locations[word[word.size() - 1]].size()) {
        reverse(word.begin(), word.end());
    }
    for (int i = 0; i < locations[word[0]].size(); i++) {
        int x = locations[word[0]][i].first, y = locations[word[0]][i].second;
        vector<vector<bool>> visited = vector<vector<bool>>(board.size(), vector<bool>(board[0].size()));
        if (recurse(board, visited, word, x, y, 1)) {
            return true;
        }
    }
    return false;
}

vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
    map<char, vector<pair<int, int>>> locations;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            locations[board[i][j]].push_back({ i, j });
        }
    }
    vector<string> ret_val;
    for (int i = 0; i < words.size(); i++) {
        if (valid(board, words[i], locations)) {
            ret_val.push_back(words[i]);
        }
    }
    return ret_val;
}

int main()
{
    vector<vector<char>> board {
        { 'o','a','a','n' },
        { 'e','t','a','e' },
        { 'i','h','k','r' },
        { 'i','f','l','v' } };
    vector<string> words { "oath","pea","eat","rain" };
    vector<string> result = findWords(board, words);
    return 0;
}