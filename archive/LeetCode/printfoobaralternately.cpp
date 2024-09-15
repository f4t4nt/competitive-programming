#include <bits/stdc++.h>

using namespace std;

class FooBar {
private:
    int n, j = 0;
    std::mutex mtx;
    std::condition_variable cv;

public:
    FooBar(int n) {
        this->n = n;
    }

    void foo(function<void()> printFoo) {
        std::unique_lock<std::mutex> lock(mtx);
        
        for (int i = 0; i < n; i++) {
            cv.wait(lock, [this] { return j % 2 == 0; });
            j++;
        	printFoo();
            cv.notify_all();
        }
    }

    void bar(function<void()> printBar) {
        std::unique_lock<std::mutex> lock(mtx);
        
        for (int i = 0; i < n; i++) {
            cv.wait(lock, [this] { return j % 2 == 1; });
            j++;
        	printBar();
            cv.notify_all();
        }
    }
};