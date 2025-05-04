#include <bits/stdc++.h>

using namespace std;

int deleteProducts(vector<int> ids, int m) {
    map<int, int> id_counts;
    for (size_t i = 0; i < ids.size(); i++) {
        id_counts[ids[i]]++;
    }
    multiset<int> counts;
    for (auto x : id_counts) {
        counts.insert(x.second);
    }
    int rv = counts.size();
    auto it = counts.begin();
    while (it != counts.end() && m >= 0) {
        m -= *it;
        rv--;
        it++;
    }
    return rv + 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<int> ids(n);
    for (int i = 0; i < n; i++) {
        cin >> ids[i];
    }
    int m;
    cin >> m;
    cout << deleteProducts(ids, m) << '\n';

    return 0;
}