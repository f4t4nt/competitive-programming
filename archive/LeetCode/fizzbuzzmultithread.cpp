#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef complex<long double> cd;
typedef long double ld;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

using indexed_set = tree<
    pld,
    null_type,
    less<pld>,
    rb_tree_tag,
    tree_order_statistics_node_update>;

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
// #define f first
// #define s second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)

// #ifdef LOCAL
// #include "tester.cpp"
// #define main test_main
// extern istringstream fin;
// extern ostringstream fout;
// string test_file_name = "tests";
// #define cin fin
// #define cout fout
// #endif

class FizzBuzzAtomic { // 1M: 130ms
private:
    int n;
    std::atomic<int> i;

public:
    FizzBuzzAtomic(int n) : n(n), i(1) {}

    void fizz() {
        while (true) {
            int current = i.load();
            if (current > n) break;
            if (current % 3 == 0 && current % 5 != 0)
                i.fetch_add(1);
        }
    }

    void buzz() {
        while (true) {
            int current = i.load();
            if (current > n) break;
            if (current % 3 != 0 && current % 5 == 0)
                i.fetch_add(1);
        }
    }

    void fizzbuzz() {
        while (true) {
            int current = i.load();
            if (current > n) break;
            if (current % 3 == 0 && current % 5 == 0)
                i.fetch_add(1);
        }
    }

    void number() {
        while (true) {
            int current = i.load();
            if (current > n) break;
            if (current % 3 != 0 && current % 5 != 0)
                i.fetch_add(1);
        }
    }
};

class FizzBuzzAtomicYield { // 1M: 180ms
private:
    int n;
    std::atomic<int> i;

public:
    FizzBuzzAtomicYield(int n) : n(n), i(1) {}

    void fizz() {
        while (true) {
            int current = i.load();
            if (current > n) break;
            if (current % 3 == 0 && current % 5 != 0)
                i.fetch_add(1);
            this_thread::yield();
        }
    }

    void buzz() {
        while (true) {
            int current = i.load();
            if (current > n) break;
            if (current % 3 != 0 && current % 5 == 0)
                i.fetch_add(1);
            this_thread::yield();
        }
    }

    void fizzbuzz() {
        while (true) {
            int current = i.load();
            if (current > n) break;
            if (current % 3 == 0 && current % 5 == 0)
                i.fetch_add(1);
            this_thread::yield();
        }
    }

    void number() {
        while (true) {
            int current = i.load();
            if (current > n) break;
            if (current % 3 != 0 && current % 5 != 0)
                i.fetch_add(1);
            this_thread::yield();
        }
    }
};

class FizzBuzzNoob { // 1M: 105ms
private:
    int n, i;

public:
    FizzBuzzNoob(int n) : n(n), i(1) {}

    void fizz() {
        while (true) {
            if (i > n) break;
            if (i % 3 == 0 && i % 5 != 0)
                i++;
        }
    }

    void buzz() {
        while (true) {
            if (i > n) break;
            if (i % 3 != 0 && i % 5 == 0)
                i++;
        }
    }

    void fizzbuzz() {
        while (true) {
            if (i > n) break;
            if (i % 3 == 0 && i % 5 == 0)
                i++;
        }
    }

    void number() {
        while (true) {
            if (i > n) break;
            if (i % 3 != 0 && i % 5 != 0)
                i++;
        }
    }
};

class FizzBuzzNotifyAll { // 100K: 4095ms
private:
    int n, i;
    std::mutex mtx;
    std::condition_variable cv;

public:
    FizzBuzzNotifyAll(int n) : n(n), i(1) {}

    void fizz() {
        while (true) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this] { return (i > n) || ((i % 3 == 0) && (i % 5 != 0)); });
            if (i++ > n) break;
            cv.notify_all();
        }
    }

    void buzz() {
        while (true) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this] { return (i > n) || ((i % 3 != 0) && (i % 5 == 0)); });
            if (i++ > n) break;
            cv.notify_all();
        }
    }

    void fizzbuzz() {
        while (true) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this] { return (i > n) || ((i % 3 == 0) && (i % 5 == 0)); });
            if (i++ > n) break;
            cv.notify_all();
        }
    }

    void number() {
        while (true) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this] { return (i > n) || ((i % 3 != 0) && (i % 5 != 0)); });
            if (i++ > n) break;
            cv.notify_all();
        }
    }
};

#define FizzBuzz FizzBuzzNotifyAll

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    FizzBuzz fb(100000);

    thread t1(&FizzBuzz::fizz, &fb);
    thread t2(&FizzBuzz::buzz, &fb);
    thread t3(&FizzBuzz::fizzbuzz, &fb);
    thread t4(&FizzBuzz::number, &fb);

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cout << "Runtime: " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " ms" << endl;

    return 0;
}