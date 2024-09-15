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
#define f first
#define s second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)
#define FOB(x, b, e) for (auto x = b; x < e; x++)
#define FORE(x, C) for (auto &x : C)

// #ifdef LOCAL
// #include "tester.cpp"
// #define main test_main
// extern istringstream fin;
// extern ostringstream fout;
// string test_file_name = "tests";
// #define cin fin
// #define cout fout
// #endif

class Option {
private:
    str keyword;
    str stat;
    int passRoom;
    str passText;
    int failRoom;
    str failText;
    int damage;

public:
    Option() {}

    Option(map<str, str> &option) {
        keyword = option["Option"];
        stat = option["Stat"];
        passRoom = getInt(option["Pexit"]);
        passText = option["Pass"];
        failRoom = getInt(option["Fexit"]);
        failText = option["Fail"];
        damage = getInt(option["Damage"]);
    }

    int getInt(const str &s) {
        if (s.empty()) {
            return 0;
        } else {
            return stoi(s);
        }
    }

    str getKeyword() const { return keyword; }

    str getStat() const { return stat; }

    int getPassRoom() const { return passRoom; }

    str getPassText() const { return passText; }

    int getFailRoom() const { return failRoom; }

    str getFailText(int damage) const {
        str result = failText;
        size_t pos = result.find("DMG");
        if (pos != str::npos) {
            result.replace(pos, 3, to_string(damage));
        }
        return result;
    }

    int getDamage() const { return damage; }
};

class Room {
private:
    int roomNumber;
    str description;
    vector<Option> options;
    map<str, int> optionsMap;

public:
    Room(int roomNumber, str description) : roomNumber(roomNumber), description(description) {}

    int getRoomNumber() const { return roomNumber; }

    str getDescription() const { return description; }

    const vector<Option> &getOptions() const { return options; }

    bool getOption(const str &keyword, Option &option) const {
        auto it = optionsMap.find(keyword);
        if (it == optionsMap.end()) {
            return false;
        }
        option = options[it->second];
        return true;
    }

    void addOption(const Option &option) {
        options.pb(option);
        optionsMap[option.getKeyword()] = options.size() - 1;
    }
};

class World {
private:
    vector<Room> rooms;
    map<int, int> roomsMap;
    int currentRoom;
    map<str, int> stats;

public:
    World(const str &filename) : currentRoom(1) {
        stats["str"] = 15;
        stats["dex"] = 15;
        stats["int"] = 10;
        stats["chr"] = 8;
        readRoomsFromFile(filename);
    }

    int getCurrentRoom() const {
        return currentRoom;
    }

    bool splitLine(const str &line, str &key, str &value) {
        size_t colonPos = line.find(':');
        if (colonPos == str::npos) {
            return false;
        }
        key = line.substr(0, colonPos);
        if (line[colonPos + 1] == ' ') {
            value = line.substr(colonPos + 2);
        } else {
            value = line.substr(colonPos + 1);
        }
        return true;
    }

    bool getLine(ifstream &fin, str &key, str &value, bool &eof) {
        str line;
        if (!getline(fin, line)) {
            eof = true;
            return false;
        }
        if (!splitLine(line, key, value)) {
            return getLine(fin, key, value, eof);
        }
        return true;
    }

    void readRoomsFromFile(const str &filename) {
        ifstream fin(filename);
        if (!fin) {
            cerr << "Error opening file " << filename << endl;
            exit(1);
        }

        bool eof = false;
        str key, value;
        getLine(fin, key, value, eof);
        map<str, str> fields;
        while (!eof) {
            fields[key] = value;
            int roomNumber = -1;
            if (key == "Room") {
                roomNumber = stoi(value);
            } elif (key == "Option") {
                roomNumber = 0;
            }
            while (getLine(fin, key, value, eof) && key != "Room" && key != "Option") {
                fields[key] = value;
            }
            if (roomNumber > 0) {
                rooms.emplace_back(roomNumber, fields["Desc"]);
            } elif (roomNumber == 0) {
                rooms.back().addOption(Option(fields));
            } else {
                cerr << "Error reading file" << endl;
                exit(1);
            }
            fields.clear();
        }

        FOR (i, sz(rooms)) {
            roomsMap[rooms[i].getRoomNumber()] = i;
        }

        fin.close();
    }

    void processOption(const Option &option) {
        int dice = rng() % 20 + 1;
        if (option.getStat() == "none" || dice <= stats[option.getStat()]) {
            cout << "Success!" << endl;
            cout << option.getPassText() << endl;
            if (option.getPassRoom() != 0) {
                currentRoom = option.getPassRoom();
            }
        } else {
            cout << "Failure!" << endl;
            cout << option.getFailText(option.getDamage()) << endl;
            if (option.getFailRoom() != 0) {
                currentRoom = option.getFailRoom();
            }
        }
    }

    void play() {
        while (currentRoom != 9999) {
            const Room &room = rooms[roomsMap[currentRoom]];
            cout << room.getDescription() << endl;
            vector<Option> options = room.getOptions();
            cout << "Options:" << endl;
            for (const auto &option : options) {
                cout << option.getKeyword() << endl;
            }
            cout << "Enter choice:" << endl;
            str choice;
            cin >> choice;
            transform(all(choice), choice.begin(), ::tolower);
            Option option;
            if (room.getOption(choice, option)) {
                processOption(option);
            } else {
                cout << "Invalid choice" << endl;
            }
            cout << endl;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    World world("rooms.txt");
    world.play();

    return 0;
}