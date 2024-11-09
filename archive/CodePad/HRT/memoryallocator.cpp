#include <bitset>

using namespace std;

class GenericAllocator {
public:
    virtual ~GenericAllocator() {}
    virtual void* allocate_memory(size_t sz) = 0;
    virtual void deallocate_memory(void* b) = 0;
};

const int MAX_BYTES = 1 << 20;

template<typename T>
class MyAllocator : public GenericAllocator {
private:
    static size_t count;
    void* t = nullptr;
    int size = 0;
    const int max_size = MAX_BYTES / sizeof(T);
    bitset<MAX_BYTES / sizeof(T)> used;
    int free_idx[MAX_BYTES / sizeof(T)];
    int start_idx = 0, end_idx = 0;

public:
    MyAllocator() {
        count = 0;
        t = this->allocate_memory(MAX_BYTES);
        for (int i = 0; i < max_size; i++) {
            free_idx[i] = i;
        }
    }

    T* allocate() {
        if (size == max_size) {
            return nullptr;
        }

        int idx = free_idx[start_idx];
        free_idx[start_idx] = -1;
        start_idx = (start_idx + 1) % max_size;
        used[idx] = 1;
        size++;

        return ((T*)t) + idx;
    }

    void deallocate(T* del) {
        int idx = del - (T*)t;
        if (idx < 0 || idx >= max_size || !used[idx]) {
            return;
        }

        used[idx] = 0;
        free_idx[end_idx] = idx;
        end_idx = (end_idx + 1) % max_size;
        size--;
    }

    ~MyAllocator() {
        if (t != nullptr) {
            this->deallocate_memory(t);
        }
    }
};
