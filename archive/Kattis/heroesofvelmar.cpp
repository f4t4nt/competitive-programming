#include <bits/stdc++.h>

using namespace std;

map<string, int> cards = {
    {"Shadow", 6},
    {"Gale", 5},
    {"Ranger", 4},
    {"Anvil", 7},
    {"Vexia", 3},
    {"Guardian", 8},
    {"Thunderheart", 6},
    {"Frostwhisper", 2},
    {"Voidclaw", 3},
    {"Ironwood", 3},
    {"Zenith", 4},
    {"Seraphina", 1}
};

int main() {
    int power[2][3] = {0};

    // int tmp = -1;

    for (int loc = 0; loc < 3; loc++) {
        for (int player = 0; player < 2; player++) {
            int cnt; cin >> cnt;
            // if (tmp == -1) tmp = cnt;
            vector<string> loc_cards(cnt);
            for (auto &s : loc_cards) {
                cin >> s;
                power[player][loc] += cards[s];
                if (s == "Thunderheart" && cnt == 4) {
                    power[player][loc] += cards[s];
                }
                if (s == "Zenith" && loc == 1) {
                    power[player][loc] += 5;
                }
                if (s == "Seraphina") {
                    power[player][loc] += cnt - 1;
                }
            }
        }
    }

    int res = 0;
    for (int loc = 0; loc < 3; loc++) {
        if (power[0][loc] > power[1][loc]) res++;
        if (power[0][loc] < power[1][loc]) res--;
    }

    // if (tmp == 1) {
    //     cout << power[0][0] << ' ' << power[0][1] << ' ' << power[0][2] << '\n';
    //     cout << power[1][0] << ' ' << power[1][1] << ' ' << power[1][2] << '\n';
    // }

    if (res > 0) {
        cout << "Player 1\n";
    } else if (res < 0) {
        cout << "Player 2\n";
    } else {
        int tot0 = power[0][0] + power[0][1] + power[0][2];
        int tot1 = power[1][0] + power[1][1] + power[1][2];
        if (tot0 > tot1) cout << "Player 1\n";
        else if (tot0 < tot1) cout << "Player 2\n";
        else cout << "Tie\n";
    }
}