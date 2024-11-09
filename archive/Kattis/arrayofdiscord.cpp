#include <bits/stdc++.h>

using namespace std;

int main() {
    int n; cin >> n;
    vector<string> nums(n);
    for (auto &x : nums) cin >> x;
    bool ok = false;
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            if (nums[i].size() == 1) {
                if (stoll(nums[i - 1]) > 0) {
                    nums[i] = "0";
                    ok = true;
                    break;
                }
            } else {
                auto tmp = nums[i];
                tmp[0] = '1';
                if (stoll(nums[i - 1]) > stoll(tmp)) {
                    nums[i][0] = '1';
                    ok = true;
                    break;
                }
            }
        }
        if (i < n - 1) {
            auto tmp = nums[i];
            tmp[0] = '9';
            if (stoll(nums[i + 1]) < stoll(tmp)) {
                nums[i][0] = '9';
                ok = true;
                break;
            }
        }
    }

    if (ok) for (auto &x : nums) cout << x << ' ';
    else cout << "impossible";
    cout << '\n';

    return 0;
}