#include <bits/stdc++.h>

using namespace std;

map<string, map<string, string>> database;
map<pair<string, string>, map<int, string>> database_history;
// <-ttl, key, field, value>
priority_queue<tuple<int, string, string, string>> ttl_queue;

bool print_logs = false;

vector<string> solution(vector<vector<string>> queries) {
    vector<string> results;
    for (auto query : queries) {
        int timestamp = stoi(query[1]);
        
        while (ttl_queue.size() > 0) {
            auto [ttl, key, field, value] = ttl_queue.top();
            ttl *= -1;
            if (ttl > timestamp) {
                break;
            } else if (database.count(key) &&
                        database[key].count(field) &&
                        database[key][field] == value)
            {
                database[key].erase(field);
                database_history[{key, field}][ttl] = "";
                if (database[key].size() == 0) {
                    database.erase(key);
                }
            }
            ttl_queue.pop();
        }
        
        if (query[0] == "SET") {
            string key = query[2],
                    field = query[3],
                    value = query[4];
            results.push_back("");
            database[key][field] = value;
            database_history[{key, field}][timestamp] = value;
        } else if (query[0] == "COMPARE_AND_SET") {
            string key = query[2],
                    field = query[3],
                    expected_value = query[4],
                    new_value = query[5];
            if (database.count(key) &&
                database[key].count(field) &&
                database[key][field] == expected_value)
            {
                results.push_back("true");
                database[key][field] = new_value;
                database_history[{key, field}][timestamp] = new_value;
            } else {
                results.push_back("false");
            }
        } else if (query[0] == "COMPARE_AND_DELETE") {
            string key = query[2],
                    field = query[3],
                    expected_value = query[4];
            if (database.count(key) &&
                database[key].count(field) &&
                database[key][field] == expected_value)
            {
                results.push_back("true");
                database[key].erase(field);
                if (database[key].size() == 0) {
                    database.erase(key);
                }
                database_history[{key, field}][timestamp] = "";
            } else {
                results.push_back("false");
            }
        } else if (query[0] == "GET") {
            string key = query[2],
                    field = query[3];
            if (database.count(key) &&
                database[key].count(field))
            {
                results.push_back(database[key][field]);
            } else {
                results.push_back("");
            }
        } else if (query[0] == "SCAN") {
            string result = "",
                    key = query[2];
            if (database.count(key) && database[key].size() > 0) {
                for (auto [field, value] : database[key]) {
                    result += field + "(" + value + "), ";
                }
                if (result.size() > 2) {
                    result.pop_back();
                    result.pop_back();
                }
            }
            results.push_back(result);
        } else if (query[0] == "SCAN_BY_PREFIX") {
            string result = "",
                    key = query[2],
                    prefix = query[3];
            if (database.count(key) && database[key].size() > 0) {
                for (auto [field, value] : database[key]) {
                    if (field.size() >= prefix.size() &&
                        field.substr(0, prefix.size()) == prefix)
                    {
                        result += field + "(" + value + "), ";   
                    }
                }
                if (result.size() > 2) {
                    result.pop_back();
                    result.pop_back();
                }
            }
            results.push_back(result);
        } else if (query[0] == "SET_WITH_TTL") {
            string key = query[2],
                    field = query[3],
                    value = query[4];
            int ttl = stoi(query[5]);
            results.push_back("");
            ttl_queue.push({-(timestamp + ttl), key, field, value});
            database[key][field] = value;
            database_history[{key, field}][timestamp] = value;
        } else if (query[0] == "COMPARE_AND_SET_WITH_TTL") {
            string key = query[2],
                    field = query[3],
                    expected_value = query[4],
                    new_value = query[5];
            int ttl = stoi(query[6]);
            if (database.count(key) &&
                database[key].count(field) &&
                database[key][field] == expected_value)
            {
                results.push_back("true");
                ttl_queue.push({-(timestamp + ttl), key, field, new_value});
                database[key][field] = new_value;
                database_history[{key, field}][timestamp] = new_value;
            } else {
                results.push_back("false");
            }
        } else if (query[0] == "GET_WHEN") {
            string key = query[2],
                    field = query[3];
            int at_timestamp = stoi(query[4]);
            if (at_timestamp == 0) {
                if (database.count(key) &&
                    database[key].count(field))
                {
                    results.push_back(database[key][field]);
                } else {
                    results.push_back("");
                }
            } else if (database_history.count({key, field})) {
                auto it = database_history[{key, field}].upper_bound(at_timestamp);
                if (it != database_history[{key, field}].begin()) {
                    it--;
                    auto [prev_timestamp, prev_value] = *it;
                    results.push_back(prev_value);
                } else {
                    results.push_back("");
                }
            } else {
                results.push_back("");
            }
        }
        
        if (print_logs) {
            cout << "timestamp " << timestamp << ":\n";
            cout << "database: {\n";
            for (auto [key, key_data] : database) {
                cout << "\"" << key << "\": {";
                for (auto [field, value] : key_data) {
                    cout << "\"" << field << "\": " << value << ", ";
                }
                cout << "}\n";
            }
            cout << "}\n\n";
        }
    }
    
    if (print_logs) {
        cout << "database_history: {\n";
        for (auto [key_field, history] : database_history) {
            auto [key, field] = key_field;
            cout << "key \"" << key << "\", field \"" << field << "\": {\n";
            for (auto [timestamp, value] : history) {
                cout << "timestamp " << timestamp << ": " << value << "\n";
            }
            cout << "}\n";
        }
        cout << "}\n\n";
    }
    
    return results;
}