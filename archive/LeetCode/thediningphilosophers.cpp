#include <bits/stdc++.h>

using namespace std;

class DiningPhilosophers {
public:
    bool forks[5];
    std::mutex mtx;
    std::condition_variable cv;

    DiningPhilosophers() {
        for (bool &f : forks) f = true;
    }

    void wantsToEat(const int idx,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) {
		std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this, idx] { return forks[idx % 5] && forks[(idx + 1) % 5]; });
        forks[idx % 5] = false, pickLeftFork();
        forks[(idx + 1) % 5] = false, pickRightFork();
        eat();
        forks[idx % 5] = true, putLeftFork();
        forks[(idx + 1) % 5] = true, putRightFork();
        cv.notify_all();
    }
};