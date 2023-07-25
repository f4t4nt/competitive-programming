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
#include <string.h>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>

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

str in_ref = "(_,_) ";

struct BinaryNode {
    char value;
    BinaryNode *left;
    BinaryNode *right;
    BinaryNode *parent;
    BinaryNode(char value, BinaryNode *parent) {
        this->value = value;
        this->parent = parent;
        this->left = nullptr;
        this->right = nullptr;
    }
};

str s_exp(vector<BinaryNode *> &nodes, BinaryNode *node) {
    if (node == nullptr) {
        return "()";
    }
    str left = s_exp(nodes, node->left);
    str right = s_exp(nodes, node->right);
    str value = str(1, node->value);
    if (left == "()" && right == "()") {
        return "(" + value + ")";
    } else if (left == "()") {
        return "(" + value + right + ")";
    } else if (right == "()") {
        return "(" + value + left + ")";
    } else {
        return "(" + value + left + right + ")";
    }
}

str solve(str &line) {
    if (line.size() % in_ref.size() != 0) {
        return "E1";
    }

    ll n = line.size() / in_ref.size();
    vector<BinaryNode *> nodes(26, nullptr);

    FOR(i, n) {
        FOR(j, in_ref.size()) {
            if (in_ref[j] != '_' && line[i * in_ref.size() + j] != in_ref[j]) {
                return "E1";
            }
        }

        char parent = line[i * in_ref.size() + 1],
                child = line[i * in_ref.size() + 3];

        if (parent == child ||
                (parent < 'A' || parent > 'Z') ||
                (child < 'A' || child > 'Z')) {
            return "E1";
        }
        if (nodes[parent - 'A'] == nullptr) {
            nodes[parent - 'A'] = new BinaryNode(parent, nullptr);
        }
        if (nodes[child - 'A'] == nullptr) {
            nodes[child - 'A'] = new BinaryNode(child, nodes[parent - 'A']);
        } else {
            if (nodes[child - 'A']->parent == nodes[parent - 'A']) {
                return "E2";
            } else if (nodes[child - 'A']->parent != nullptr) {
                return "E1";
            } else {
                nodes[child - 'A']->parent = nodes[parent - 'A'];
            }
        }
        if (nodes[parent - 'A']->left == nullptr) {
            nodes[parent - 'A']->left = nodes[child - 'A'];
        } else if (nodes[parent - 'A']->right == nullptr) {
            nodes[parent - 'A']->right = nodes[child - 'A'];
        } else {
            return "E3";
        }
    }

    BinaryNode *root = nullptr;
    ll vertex_count = 0;
    FOR(i, 26) {
        if (nodes[i] != nullptr) {
            vertex_count++;
            if (nodes[i]->parent == nullptr) {
                if (root == nullptr) {
                    root = nodes[i];
                } else {
                    return "E4";
                }
            }
            if (nodes[i]->left != nullptr && nodes[i]->right != nullptr) {
                if (nodes[i]->left->value > nodes[i]->right->value) {
                    swap(nodes[i]->left, nodes[i]->right);
                }
            }
        }
    }
    if (vertex_count != n + 1) {
        return "E5";
    }

    return s_exp(nodes, root);
}

int main() {
    str line;
    getline(cin, line);
    line += " ";
    cout << solve(line);
    return 0;
}