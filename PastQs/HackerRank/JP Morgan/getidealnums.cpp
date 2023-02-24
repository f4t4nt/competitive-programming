#include <bits/stdc++.h>

using namespace std;

long getIdealNums(long low, long high) {
    vector<long> pow3(21), pow5(15);
    long curr3 = 1, curr5 = 1;
    for (int i = 0; i < 21; i++) {
        pow3[i] = curr3;
        curr3 *= 3;
    }
    for (int i = 0; i < 15; i++) {
        pow5[i] = curr5;
        curr5 *= 5;
    }
    long rv = 0;
    for (int i = 0; i < 21; i++) {
        if (pow3[i] > high) {
            break;
        }
        int lo = 0;
        while (pow3[i] * pow5[lo] < low) {
            lo++;
        }
        int hi = lo;
        while (pow3[i] * pow5[hi] <= high) {
            hi++;
        }
        rv += hi - lo;
    }
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    long low, high;
    cin >> low >> high;
    cout << getIdealNums(low, high) << '\n';

    return 0;
}