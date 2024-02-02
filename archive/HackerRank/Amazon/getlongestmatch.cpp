#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the 'getLongestMatch' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. STRING text
 *  2. STRING regex
 */

typedef long long ll;

const ll ALPHA = 27;
const ll MOD = 1e12 + 7;
vector<ll> pows(1e6 + 1, 1);

int find_first_idx(string &txt, string &rgx) {
    // cerr << txt << " " << rgx << "\n";
    ll hash = 0, cur = 0;
    for (ll i = 0; i < (ll) rgx.size(); i++) {
        hash *= ALPHA;
        hash += rgx[i] - 'a' + 1;
        hash %= MOD;
    }
    // cerr << hash << "\n";
    for (int i = 0; i < (int) txt.size(); i++) {
        cur *= ALPHA;
        cur += txt[i] - 'a' + 1;
        cur %= MOD;
        if (i >= (int) rgx.size()) {
            cur -= (txt[i - (int) rgx.size()] - 'a' + 1) * pows[(int) rgx.size()];
            while (cur < 0) cur += MOD;
            cur %= MOD;
        }
        // cerr << i << " " << cur << "\n";
        if (hash == cur) {
            return i;
        }
    }
    return -1;
}

int getLongestMatch(string text, string regex) {
    // cerr << text << " " << regex;
    int split_idx = 0;
    while (regex[split_idx] != '*') {
        split_idx++;
    }
    string rgx_lo = regex.substr(0, split_idx), rgx_hi = regex.substr(split_idx + 1, (int) regex.size() - split_idx - 1);
    // int lo = -1, hi = -1;
    // for (int i = 0; i < (int) text.size() - (int) rgx_lo.size(); i++) {
    //     if (rgx_lo == text.substr(i, (int) rgx_lo.size())) {
    //         lo = i;
    //         break;
    //     }
    // }
    // if (lo == -1) return -1;
    // for (int i = (int) text.size() - (int) rgx_hi.size(); i >= 0; i--) {
    //     if (rgx_hi == text.substr(i, (int) rgx_hi.size())) {
    //         hi = i;
    //         break;
    //     }
    // }
    // if (hi == -1) return -1;
    // int len = hi + (int) rgx_hi.size() - lo;
    // if (len < regex.size() - 1) return -1;
    // return len;
    for (ll i = 0; i < 1e6; i++) pows[i + 1] = (pows[i] * ALPHA) % MOD;
    int lo, hi;
    if ((int) rgx_lo.size() > 0) {
        lo = find_first_idx(text, rgx_lo);
        // cerr << lo << "\n";
        if (lo == -1) return -1;
        lo -= (int) rgx_lo.size() - 1;
        // cerr << text.substr(lo, rgx_lo.size()) << "\n";
    } else {
        lo = 0;
    }
    if ((int) rgx_hi.size() > 0) {
        string rev_text = text, rev_rgx_hi = rgx_hi;
        reverse(rev_text.begin(), rev_text.end());
        reverse(rev_rgx_hi.begin(), rev_rgx_hi.end());
        int rev_hi = find_first_idx(rev_text, rev_rgx_hi);
        // cerr << rev_hi << "\n";
        if (rev_hi == -1) return -1;
        // cerr << rev_text.substr(rev_hi - (int) rev_rgx_hi.size() + 1, rev_rgx_hi.size()) << "\n";
        hi = text.size() - rev_hi - 1;
        // cerr << hi << "\n";
        // cerr << text.substr(hi, rgx_hi.size()) << "\n";
    } else {
        hi = (int) text.size() - rgx_hi.size();
    }
    int len = hi + (int) rgx_hi.size() - lo;
    if (len < (int) regex.size() - 1) return -1;
    return len;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string text;
    getline(cin, text);

    string regex;
    getline(cin, regex);

    int result = getLongestMatch(text, regex);

    fout << result << "\n";

    fout.close();

    return 0;
}