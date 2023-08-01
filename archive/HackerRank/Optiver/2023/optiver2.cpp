#include <bits/stdc++.h>

using namespace std;

struct LionDescription
{
    string name;
    int height;
};

struct LionSchedule
{
    string name;
    int enterTime;
    int exitTime;
};

class LionCompetition
{
    // {name of lion} -> {size}
    map<string, int> my_lion_sizes;
    // {enter} -> {names of lions}
    map<pair<int, int>, set<string>> my_lion_enters,
    // {exit} -> {names of lions}
        my_lion_exits;
    // sizes of other lions
    multiset<int> other_active_lions;
    // sizes of my active lions
    set<pair<int, string>> my_active_lions;
public:
    void print_details(bool init = false) {
        if (init) {
            cout << "my_lion_sizes:\n";
            for (auto &elem : my_lion_sizes) {
                cout << "{" << elem.first << "} -> {" << elem.second << "}\n";
            }
            cout << "\n";
            cout << "my_lion_enters:\n";
            for (auto &elem : my_lion_enters) {
                cout << "{" << elem.first.first << "," << elem.first.second << "} -> {";
                for (auto &name : elem.second) {
                    cout << name << ",";
                }
                cout << "}\n";
            }
            cout << "\n";
            cout << "my_lion_exits:\n";
            for (auto &elem : my_lion_exits) {
                cout << "{" << elem.first.first << "," << elem.first.second << "} -> {";
                for (auto &name : elem.second) {
                    cout << name << ",";
                }
                cout << "}\n";
            }
            cout << "\n";
        }
        cout << "other_active_lions:\n";
        cout << "{";
        for (auto &elem : other_active_lions) {
            cout << elem << ",";
        }
        cout << "}\n";
        cout << "my_active_lions:\n";
        cout << "{";
        for (auto &elem : my_active_lions) {
            cout << "{" << elem.first << "," << elem.second << "},";
        }
        cout << "}\n";
        cout << "\n";
    }

    LionCompetition(list<LionDescription> lions, list<LionSchedule> schedule)
    {
        // cout << "Got details\n";
        for (auto &lion_data : lions) {
            my_lion_sizes[lion_data.name] = lion_data.height;
        }
        for (auto &lion_times : schedule) {
            my_lion_enters[{my_lion_sizes[lion_times.name], lion_times.enterTime}].insert(lion_times.name);
            my_lion_exits[{my_lion_sizes[lion_times.name], lion_times.exitTime}].insert(lion_times.name);
        }
        // print_details(true);
    }

    void lionEntered(int currentTime, int height)
    {
        // cout << "Processing enter currentTime = " << currentTime << ", height = " << height << "\n";
        if (my_lion_enters.count({height, currentTime})) {
            auto it = my_lion_enters[{height, currentTime}].begin();
            my_active_lions.insert({height, *it});
            my_lion_enters[{height, currentTime}].erase(it);
            if (my_lion_enters[{height, currentTime}].size() == 0) {
                my_lion_enters.erase({height, currentTime});
            }
        } else {
            other_active_lions.insert(height);
        }
        // print_details();
    }

    void lionLeft(int currentTime, int height)
    {
        // cout << "Processing exit currentTime = " << currentTime << ", height = " << height << "\n";
        if (my_lion_exits.count({height, currentTime})) {
            auto it = my_lion_exits[{height, currentTime}].begin();
            my_active_lions.erase({height, *it});
            my_lion_exits[{height, currentTime}].erase(it);
            if (my_lion_exits[{height, currentTime}].size() == 0) {
                my_lion_exits.erase({height, currentTime});
            }
        } else {
            other_active_lions.erase(other_active_lions.find(height));
        }
        // print_details();
    }

    list<string> getBiggestLions()
    {
        // cout << "Getting biggest lions\n";
        int max_height = 0;
        if (other_active_lions.size()) {
            max_height = *other_active_lions.rbegin();
        }
        list<string> rv;
        if (my_active_lions.size()) {
            auto it = my_active_lions.rbegin();
            while (it != my_active_lions.rend() && it->first >= max_height) {
                rv.push_back(it->second);
                it++;
            }
        }
        // for (auto &lion : my_active_lions) {
        //     if (lion.first >= max_height) {
        //         rv.push_back(lion.second);
        //     }
        // }
        // if (rv.size()) { // IDK HOW TO SORT WITH C++11
        //     sort(rv, rv + rv.size());
        // }
        // print_details();
        return rv;
    }
};
int main()
{
	string operation;

	list<LionDescription> descriptions;
	list<LionSchedule> schedule;

	do
	{
		cin >> operation;

		if (operation == "definition")
		{
			string name;
			int size;
			cin >> name >> size;

			descriptions.push_back({name, size});
		}
		if (operation == "schedule")
		{
			string name;
			int enterTime;
			int exitTime;
			cin >> name >> enterTime >> exitTime;

			schedule.push_back({name, enterTime, exitTime});
		}
	} while (operation != "start");

	LionCompetition lionCompetition(descriptions, schedule);

	do
	{
		int currentTime;
		cin >> currentTime >> operation;

		if (operation == "enter")
		{
			int size;
			cin >> size;

			lionCompetition.lionEntered(currentTime, size);
		}
		if (operation == "exit")
		{
			int size;
			cin >> size;

			lionCompetition.lionLeft(currentTime, size);
		}
		if (operation == "inspect")
		{
			list<string> lions = lionCompetition.getBiggestLions();

			cout << lions.size();

			for (const string &name : lions)
			{
				cout << " " << name;
			}

			cout << "\n";
		}
	}
	while (operation != "end");

	return 0;
}