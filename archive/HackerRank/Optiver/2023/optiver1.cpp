#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

class IPrinter
{
public:
    virtual ~IPrinter() = default;
    virtual void OnMessageComplete(const std::string& message) const = 0;
};

class Printer
    : public IPrinter
{
public:
    void OnMessageComplete(const std::string& message) const override
    {
        std::cout << message << std::endl;
    }
};

class Decoder
{
    uint64_t last_completed = 0;
    map<uint64_t, string> all_messages;
public:
    Decoder(const IPrinter& printer)
        : mPrinter(printer)
    {
    }
    
    void print_messages() {
        cout << "last_completed: " << last_completed << "\n";
        cout << "all_messages:\n";
        for (auto &elem : all_messages) {
            cout << elem.first << ": " << elem.second << ", " << elem.second.size() << "\n";
        }
    }
    
    void ProcessSample(const uint64_t sequence, const char character)
    {
        if (character == '-') {
            all_messages[sequence] = string(1, character);
        } else {
            if (all_messages.count(sequence + 1)) {
                string next = all_messages[sequence + 1];
                if (next != "-") {
                    all_messages.erase(sequence + 1);
                    all_messages[sequence] = character + next;
                }
            }
            if (!all_messages.count(sequence)) {
                all_messages[sequence] = string(1, character);
            }
            auto it = all_messages.lower_bound(sequence);
            if (it != all_messages.begin()) {
                it--;
                if (it->second != "-" && it->first + (it->second).size() == sequence) {
                    string next = all_messages[sequence];
                    all_messages.erase(sequence);
                    all_messages[it->first] += next;
                }
            }
        }
        auto it = all_messages.lower_bound(sequence);
        int idx = 0;
        while (idx <= 5 && it != all_messages.end()) {
            it++;
            idx++;
        }
        it--;
        while (idx >= -5 && it != all_messages.begin()) {
            if (it->second != "-") {
                if (all_messages.count(it->first - 1) && all_messages[it->first - 1] == "-" &&
                    all_messages.count(it->first + (it->second).size()) && all_messages[it->first + (it->second).size()] == "-" &&
                    it->first > last_completed
                ) {
                    mPrinter.OnMessageComplete(it->second);
                    last_completed = it->first;
                }
            }
            it--;
            idx--;
        }
        // print_messages();
        // cout << "===PROCESSED===\n";
    }
    
    const IPrinter& mPrinter;
};


int main() {
    Printer printer;
    Decoder decoder(printer);
    
    uint64_t seqNum;
    char message;
    
    while(!std::cin.eof())
    {
        std::cin >> seqNum >> message;
        if (std::cin.eof()) break;
        decoder.ProcessSample(seqNum, message);
    }
    
    return  0;
}