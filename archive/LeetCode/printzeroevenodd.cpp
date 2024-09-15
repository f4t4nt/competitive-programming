#include <bits/stdc++.h>

using namespace std;

class ZeroEvenOdd {
private:
    int n, cnt = 0;
    std::mutex mtx;
    std::condition_variable cv;

public:
    ZeroEvenOdd(int n) {
        this->n = n;
    }

    void zero(function<void(int)> printNumber) {
        std::unique_lock<std::mutex> lock(mtx);
        while (cnt < 2 * n) {
            cv.wait(lock, [this] { return cnt % 2 == 0 || cnt == 2 * n; });
            if (cnt++ < 2 * n) printNumber(0);
            cv.notify_all();
        }
        cv.notify_all();
    }

    void even(function<void(int)> printNumber) {
        std::unique_lock<std::mutex> lock(mtx);
        while (cnt < 2 * n) {
            cv.wait(lock, [this] { return cnt % 4 == 3 || cnt == 2 * n; });
            if (cnt++ < 2 * n) printNumber(cnt / 2);
            cv.notify_all();
        }
        cv.notify_all();
    }

    void odd(function<void(int)> printNumber) {
        std::unique_lock<std::mutex> lock(mtx);
        while (cnt < 2 * n) {
            cv.wait(lock, [this] { return cnt % 4 == 1 || cnt == 2 * n; });
            if (cnt++ < 2 * n) printNumber(cnt / 2);
            cv.notify_all();
        }
        cv.notify_all();
    }
};