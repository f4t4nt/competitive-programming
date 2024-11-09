#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    // vector<pair<int, int>> getSubexprIdxs(const string &expression, int lo, int hi) {
    //     int bracket_depth = 0, subexpr_start = lo + 2;
    //     vector<pair<int, int>> subexpr_idxs;
    //     for (int idx = lo + 2; idx < hi - 1; idx++) {
    //         if (expression[idx] == '(') {
    //             bracket_depth++;
    //         } else if (expression[idx] == ')') {
    //             bracket_depth--;
    //         } else if (bracket_depth == 0 && expression[idx] == ',') {
    //             subexpr_idxs.push_back({subexpr_start, idx});
    //             subexpr_start = idx + 1;
    //         }
    //     }
    //     subexpr_idxs.push_back({subexpr_start, hi - 1});
    //     return subexpr_idxs;
    // }

    bool parseBoolExpr(const string &expression, int lo = 0, int hi = -1) {
        // // cerr << lo << ' ' << hi << endl;
        // if (hi == -1) {
        //     hi = expression.size();
        // }
        // assert(lo < hi);
        // if (lo + 1 == hi) {
        //     assert(expression[lo] == 't' || expression[lo] == 'f');
        //     return expression[lo] == 't';
        // } else if (expression[lo] == '!') {
        //     return !parseBoolExpr(expression, lo + 2, hi - 1);
        // } else if (expression[lo] == '&') {
        //     vector<pair<int, int>> subexpr_idxs = getSubexprIdxs(expression, lo, hi);
        //     for (auto [lo_subexpr, hi_subexpr] : subexpr_idxs) {
        //         if (!parseBoolExpr(expression, lo_subexpr, hi_subexpr)) {
        //             return false;
        //         }
        //     }
        //     return true;
        // } else if (expression[lo] == '|') {
        //     vector<pair<int, int>> subexpr_idxs = getSubexprIdxs(expression, lo, hi);
        //     for (auto [lo_subexpr, hi_subexpr] : subexpr_idxs) {
        //         if (parseBoolExpr(expression, lo_subexpr, hi_subexpr)) {
        //             return true;
        //         }
        //     }
        //     return false;
        // } else {
        //     assert(false);
        // }

        string stk = "";
        stk.reserve(expression.size());
        for (char c : expression) {
            stk += c;
            if (c == ')') {
                // vector<bool> subexpressions;
                bool not_res = false, and_res = true, or_res = false;
                stk.pop_back();
                while (stk.back() != '(') {
                    // if (stk.back() == 't') subexpressions.push_back(true);
                    // else if (stk.back() == 'f') subexpressions.push_back(false);
                    if (stk.back() == 't') {
                        not_res = false;
                        or_res = true;
                    } else if (stk.back() == 'f') {
                        not_res = true;
                        and_res = false;
                    }
                    stk.pop_back();
                }
                stk.pop_back();
                if (stk.back() == '!') {
                    // assert(subexpressions.size() == 1);
                    stk.pop_back();
                    // if (subexpressions[0]) stk += 'f';
                    // else if (!subexpressions[0]) stk += 't';
                    // else assert(false);
                    if (not_res) stk += 't';
                    else stk += 'f';
                } else if (stk.back() == '&') {
                    stk.pop_back();
                    // bool ok = true;
                    // for (bool e : subexpressions) {
                    //     ok &= e;
                    //     if (!ok) break;
                    // }
                    // if (ok) stk += 't';
                    // else stk += 'f';
                    if (and_res) stk += 't';
                    else stk += 'f';
                } else if (stk.back() == '|') {
                    stk.pop_back();
                    // bool ok = false;
                    // for (bool e : subexpressions) {
                    //     ok |= e;
                    //     if (ok) break;
                    // }
                    // if (ok) stk += 't';
                    // else stk += 'f';
                    if (or_res) stk += 't';
                    else stk += 'f';
                } else assert(false);
            }
        }
        assert(stk == "t" || stk == "f");
        return stk == "t";
    }
};
