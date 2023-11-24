// weighted moving averages

#include <bits/stdc++.h>
using namespace std;

int main() {
  cout << fixed << setprecision(2);
  string line;
  while (getline(cin, line)) {
    replace(line.begin(), line.end(), ',', ' ');
    replace(line.begin(), line.end(), ';', ' ');
    istringstream iss(line);
    // {id, sum, qty}
    map<int, pair<double, double>> ref;
    int max_seq_id = -1;
    int key, seq_id;
    double val, qty;
    while (iss >> key >> val >> qty >> seq_id) {
      if (seq_id < max_seq_id) {
        continue;
      }
      max_seq_id = seq_id;
      ref[key].first += val * qty;
      ref[key].second += qty;
      // cout << ref[key].first << ' ' << ref[key].second << '\n';
      cout << key << ": " << ref[key].first / ref[key].second << '\n';
    }
    // cout << line << '\n';
  }
}