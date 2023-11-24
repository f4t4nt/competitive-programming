#include <vector>

/// The definition of a buy or a sell order targeting a particular concert's tickets.
/// @member timestamp The time at which the order request was made.
/// @member concertId The ID of the concert whose tickets to either buy or sell.
/// @member buy Whether the order is to buy ('true') or sell ('false') tickets to the concert.
/// @member quantity The number of concert ticks to buy or sell.
struct Order { int timestamp; int concertId; bool buy; int quantity; };

/// The definition of an update to the price of a ticket for a concert.
/// @member timestamp The time at which the change in price took effect.
/// @member concertId The ID of the concert whose ticket price changed.
/// @member delta The amount that the concert's ticket price increased (if positive) or decreased (if negative).
struct PriceUpdate { int timestamp; int concertId; int delta; };


/// @param initialPrice The price of tickets for all concerts at the beginning of the day, before any price updates are
///   published.
/// @param orders The sequence of buy and sell orders to be executed.
/// @param feed The exchange feed of price updates to various concerts' ticket prices.
/// @pre @p initialPrice >= 1.
/// @pre @p orders is not empty, and is sorted in ascending order by timestamp.
/// @pre @p feed is not empty, and is sorted in ascending order by timestamp.
/// @pre @p The set of all timestamps among orders in @p orders and price updates in @p feed contains no duplicates.
/// @returns A collection [see below] with the end-of-day profits and losses of each concert for which at least one order
///   was executed. Concerts for which a ticket price update was published but no orders were executed should be excluded
///   from the return value.
#include <map>
using namespace std;
vector<pair<int, int>> ticketsMargin(int initialPrice, const std::vector<Order> &orders, const std::vector<PriceUpdate> &feed) {
    // {id, price}, {id, del}
    map<int, int> prices, rv_map;
    size_t i = 0, j = 0;
    while (i < orders.size() || j < feed.size()) {
        if (i == orders.size()) {
            if (prices.find(feed[j].concertId) == prices.end()) {
                prices[feed[j].concertId] = initialPrice;
            }
            prices[feed[j].concertId] += feed[j].delta;
            j++;
        } else if (j == feed.size()) {
            if (prices.find(orders[i].concertId) == prices.end()) {
                prices[orders[i].concertId] = initialPrice;
            }
            if (orders[i].buy) {
                rv_map[orders[i].concertId] -= prices[orders[i].concertId] * orders[i].quantity;
            } else {
                rv_map[orders[i].concertId] += prices[orders[i].concertId] * orders[i].quantity;
            }
            i++;
        } else if (orders[i].timestamp < feed[j].timestamp) {
            if (prices.find(orders[i].concertId) == prices.end()) {
                prices[orders[i].concertId] = initialPrice;
            }
            if (orders[i].buy) {
                rv_map[orders[i].concertId] -= prices[orders[i].concertId] * orders[i].quantity;
            } else {
                rv_map[orders[i].concertId] += prices[orders[i].concertId] * orders[i].quantity;
            }
            i++;
        } else if (orders[i].timestamp > feed[j].timestamp) {
            if (prices.find(feed[j].concertId) == prices.end()) {
                prices[feed[j].concertId] = initialPrice;
            }
            prices[feed[j].concertId] += feed[j].delta;
            j++;
        }
    }
    vector<pair<int, int>> rv;
    for (auto &e : rv_map) {
        rv.push_back({e.first, e.second});
    }
    return rv;
}

#include <algorithm>
#include <fstream>
#include <iostream>

int readInteger(bool wholeLine);


int main() {
    // read in test case
    int initialPrice = readInteger(true);
    std::vector<PriceUpdate> feed{};
    const int numPriceUpdates = readInteger(true);
    for (int i = 0; i < numPriceUpdates; ++i) {
        int ts = readInteger(false);
        int id = readInteger(false);
        int delta = readInteger(true);
        feed.push_back({ ts, id, delta });
    }
    std::vector<Order> orders{};
    const int numOrders = readInteger(true);
    for (int i = 0; i < numOrders; ++i) {
        int ts = readInteger(false);
        int id = readInteger(false);
        bool buy = readInteger(false) == 1 ? true : false;
        int qty = readInteger(true);
        orders.push_back({ ts, id, buy, qty });
    }
    
    // execute function
    const auto result = ticketsMargin(initialPrice, orders, feed);
    
    // organize result
    std::vector<std::pair<int, int>> pairs{};
    for (auto &&element : result) {
        auto [a, b] = element;
        int concertId = a;
        int margin = b;
        pairs.emplace_back(concertId, margin);
    }
    auto comp = [](const auto &lhs, const auto &rhs) { return lhs.first < rhs.first; };
    std::sort(pairs.begin(), pairs.end(), comp);
    
    // write output to file
    constexpr auto PATH_ENV_VAR = "OUTPUT_PATH";
    const auto outputPath = getenv(PATH_ENV_VAR);
    std::ofstream outfile(outputPath);
    for (auto &&pair : pairs) {
        outfile << "(" << pair.first << ", " << pair.second << ")" << std::endl;
    }
    
    // clean up
    outfile.close();
    
    // return
    return 0;
}


int readInteger(bool wholeLine) {
    int value{};
    std::cin >> value;
    if (wholeLine) { std::cin >> std::ws; }
    return value;
}