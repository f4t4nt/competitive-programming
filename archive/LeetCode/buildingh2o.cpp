#include <bits/stdc++.h>

using namespace std;

class H2O {
public:
    int hydrogen_count, oxygen_count;
    std::mutex mtx;
    std::condition_variable cv;

    H2O() : hydrogen_count(0), oxygen_count(0) {}

    void hydrogen(std::function<void()> releaseHydrogen) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return hydrogen_count < 2; });
        hydrogen_count++;
        
        releaseHydrogen();

        if (hydrogen_count == 2 && oxygen_count == 1) {
            hydrogen_count = 0;
            oxygen_count = 0;
        }
        cv.notify_all();
    }

    void oxygen(std::function<void()> releaseOxygen) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return oxygen_count < 1; });
        oxygen_count++;
        
        releaseOxygen();

        if (hydrogen_count == 2 && oxygen_count == 1) {
            hydrogen_count = 0;
            oxygen_count = 0;
        }
        cv.notify_all();
    }
};