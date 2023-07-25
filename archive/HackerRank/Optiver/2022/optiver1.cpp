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

int DaysInMonth(int month, int year) {
    if (month == 2) {
        if (year % 4 == 0) {
            if (year % 100 == 0) {
                if (year % 400 == 0) {
                    return 29;
                } else {
                    return 28;
                }
            } else {
                return 29;
            }
        } else {
            return 28;
        }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    } else {
        return 31;
    }
}

int DaysBetween(int year1, int month1, int day1, int year2, int month2, int day2) {
    int days = 0;
    if (year1 == year2) {
        if (month1 == month2) {
            days = day2 - day1;
        } else {
            days = DaysInMonth(month1, year1) - day1;
            month1++;
            while (month1 < month2) {
                days += DaysInMonth(month1, year1);
                month1++;
            }
            days += day2;
        }
    } else {
        days = DaysInMonth(month1, year1) - day1;
        month1++;
        while (month1 <= 12) {
            days += DaysInMonth(month1, year1);
            month1++;
        }
        year1++;
        while (year1 < year2) {
            days += 365;
            if (year1 % 4 == 0) {
                if (year1 % 100 == 0) {
                    if (year1 % 400 == 0) {
                        days++;
                    }
                } else {
                    days++;
                }
            }
            year1++;
        }
        month1 = 1;
        while (month1 < month2) {
            days += DaysInMonth(month1, year1);
            month1++;
        }
        days += day2;
    }
    return days;
}

int main() {
    int year1, month1, day1, year2, month2, day2;
    cin >> year1 >> month1 >> day1 >> year2 >> month2 >> day2;
    cout << DaysBetween(year1, month1, day1, year2, month2, day2);
    return 0;
}