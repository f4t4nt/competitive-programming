#include <bits/stdc++.h>
using namespace std;
// Binary trees are already defined with this interface:
template<typename T>
struct Tree {
  Tree(const T &v) : value(v), left(nullptr), right(nullptr) {}
  T value;
  Tree *left;
  Tree *right;
};
// {ok?, min, max}
tuple<bool, int, int> recurse(Tree<int> &v) {
    tuple<bool, int, int> rv = {true, v.value, v.value};
    if (v.right != nullptr) {
        auto tmp = recurse(*v.right);
        get<0>(rv) &= get<0>(tmp) && (get<1>(tmp) > v.value);
        get<1>(rv) = min(get<1>(rv), get<1>(tmp));
        get<2>(rv) = max(get<2>(rv), get<2>(tmp));
    }
    if (v.left != nullptr) {
        auto tmp = recurse(*v.left);
        get<0>(rv) &= get<0>(tmp) && (get<2>(tmp) < v.value);
        get<1>(rv) = min(get<1>(rv), get<1>(tmp));
        get<2>(rv) = max(get<2>(rv), get<2>(tmp));
    }
    return rv;
}

bool solution(Tree<int> * t) {
    if (t == nullptr) {
        return true;
    }
    return get<0>(recurse(*t));
}
