#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> getNoZeroIntegers(int n) {
        int a = 0, b = 0, power = 1;
        while (n > 0) {
            int digit = n % 10;
            if (digit == 0) {
                a += 5 * power;
                b += 5 * power;
                n -= 10;
            } else if (digit == 1 && n >= 10) {
                a += 5 * power;
                b += 6 * power;
                n -= 11;
            } else {
                int half = digit / 2;
                a += half * power;
                b += (digit - half) * power;
            }
            power *= 10;
            n /= 10;
        }
        return {a, b};
    }
};
