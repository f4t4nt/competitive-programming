#include <bits/stdc++.h>
using namespace std;

void read_market_data(deque<pair<int, double>> &deq) {
  string line;
  getline(cin, line);
  istringstream iss(line);
  int qty;
  double val;
  while (iss >> qty >> val) {
    deq.push_back({qty, val});
  }
}

double pop_deque(int risk, deque<pair<int, double>> &deq) {
  int risk0 = risk, cur_cnt;
  double val = 0, cur_val;
  while (risk > 0) {
    cur_cnt = deq.front().first;
    cur_val = deq.front().second;
    deq.pop_front();
    risk -= cur_cnt;
    val += cur_val * (double) cur_cnt;
  }
  if (risk < 0) {
    deq.push_front({-risk, cur_val});
    val += cur_val * (double) risk;
  }
  return val / (double) risk0;
}

int main() {
  cout << fixed << setprecision(2);
  string line;
  // {qty, val}
  deque<pair<int, double>> buy, sell;
  read_market_data(buy);
  read_market_data(sell);
  // cout << buy.size() << ' ' << sell.size() << '\n';
  double risk = 0;
  double qty_risk, cur_risk;
  while (getline(cin, line)) {
    // cout << line << '\n';
    istringstream iss(line);
    iss >> qty_risk >> cur_risk;
    risk += qty_risk * cur_risk;
    int int_risk = -trunc(risk);
    risk += int_risk;
    double val = 0;
    if (int_risk > 0) { // pop buy
      val += pop_deque(int_risk, buy);
    } else if (int_risk < 0) { // pop sell
      val += pop_deque(-int_risk, sell);
    }
    cout << int_risk << ' ' << val << '\n';
  }
}