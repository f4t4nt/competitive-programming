/*

The RuleManager is a class that will exist within a trading system. It controls when the system is permitted to trade (halted=False) or restricted from trading (halted=True).
The RuleManager takes two inputs: Price Rules and Prices. Price Rules define the maximum percentage price movement from the first seen price that can occur before trading is restricted. Price updates provide the latest price.

Next the RuleManager needs to handle symbol dependencies. If a child symbol is dependent on a parent symbol, the child is halted if and only if both (a) the child symbol breaches its own price rule and (b) the parent node is halted from trading.


class RuleManager

  # to implement
  - onPriceUpdate(string ticker, double latestPrice)
  - onPriceRule(string ticker, double priceMove)
  - isHalted(string ticker)
  - addDependency(string parentTicker, string childTicker)

E.g.,
restrictionMgr.onPriceRule("AAPL", .10)
restrictionMgr.onPriceUpdate("AAPL", 2)
restrictionMgr.onPriceUpdate("AAPL", 2.15)
assert(restrictionMgr.isHalted("AAPL"))

E.g.
rulemanager.addPriceRule("AAPL_STOCK", .10)
rulemanager.addPriceRule("AAPL_BOND", .02)
rulemanager.addDependency("AAPL_STOCK"  parent  , "AAPL_BOND"  child )
rulemanager.onPriceUpdate("AAPL_STOCK", 1.0)
rulemanager.onPriceUpdate("AAPL_BOND", 1.0)
rulemanager.onPriceUpdate("AAPL_BOND", 1.5)

assert(rulemanager.state["AAPL_STOCK"] == False)
assert(rulemanager.state["AAPL_BOND"] == False)

rulemanager.onPriceUpdate("AAPL_STOCK", 1.5)
assert(rulemanager.state["AAPL_STOCK"] == True)
assert(rulemanager.state["AAPL_BOND"] == True)

*/

#include <bits/stdc++.h>

using namespace std;

struct RuleManager {
private:
    map<string, double> rules;
    map<string, double> prices;
    map<string, bool> violated;
    map<string, bool> halted;
    map<string, vector<string>> children;
    map<string, vector<string>> parents;

    void try_halt(string ticker) {
        if (!violated[ticker]) return;

        bool parents_halted = true;
        for (auto &parent : parents[ticker]) {
            if (!halted[parent]) {
                parents_halted = false;
                break;
            }
        }

        if (parents_halted) {
            halted[ticker] = true;

            for (auto &child : children[ticker]) {
                try_halt(child);
            }
        }
    }

public:
    RuleManager() {}

    void onPriceRule(string ticker, double priceMove) {
        halted[ticker] = false;
        violated[ticker] = false;
        rules[ticker] = priceMove;
    }

    void onPriceUpdate(string ticker, double latestPrice) {
        if (rules.count(ticker)) {
            double prvPrice = latestPrice;
            if (prices.count(ticker)) prvPrice = prices[ticker];

            cout << prvPrice << ' ' << latestPrice << endl;
            cout << abs((latestPrice - prvPrice) / prvPrice) << ' ' << rules[ticker] << endl;

            if (abs((latestPrice - prvPrice) / prvPrice) >= rules[ticker]) {
                cout << "halted" << endl;

                violated[ticker] = true;
                try_halt(ticker);
            }
        }

        prices[ticker] = latestPrice;
    }

    bool isHalted(string ticker) {
        // if (!halted.count(ticker)) halted[ticker] = false;

        auto it = halted.find(ticker);
        if (it == halted.end()) return false;
        else return it->second;

        // it->first key, it->second value

        // it++;
        // it += 2;

        return halted[ticker];
    }
};

int main() {
    RuleManager restrictionMgr;

    restrictionMgr.onPriceRule("AAPL", .10);
    restrictionMgr.onPriceUpdate("AAPL", 2);
    restrictionMgr.onPriceUpdate("AAPL", 1.5);
    restrictionMgr.onPriceRule("AAPL", .10);

    assert(restrictionMgr.isHalted("AAPL"));

    cout << "ok" << endl;

    return 0;
}