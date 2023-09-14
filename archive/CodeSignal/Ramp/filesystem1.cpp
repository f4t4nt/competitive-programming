#include <bits/stdc++.h>
 
using namespace std;

struct Item {
    string name = "";
    int sz = 0;
    bool is_file = false;
    map<string, Item*> subitems;
    Item* parent; // unused
    void print(int depth = 0) {
        for (int d = 0; d < depth; d++) {
            cout << "   ";
        }
        cout << name << ' ' << sz << ' ' << is_file << '\n';
        for (auto [iname, item] : subitems) {
            item->print(depth + 1);
        }
    }
};

vector<string> get_path(string &path_str) {
    vector<string> rv;
    string cur = "/";
    int idx = 1;
    while (idx < path_str.size()) {
        if (path_str[idx] == '/') {
            rv.push_back(cur);
            cur = "/";
        } else {
            cur += path_str[idx];
        }
        idx++;
    }
    rv.push_back(cur);
    return rv;
}

// go to path, if mod true then we add items as necessary
// if mod false and unable, return nullptr
// returns true if we had to mod
pair<Item*, bool> navigate(int idx, vector<string> &path, Item &cur_item, bool mod = false) {
    if (idx == path.size()) {
        return {&cur_item, false};
    }
    if (cur_item.subitems.count(path[idx])) {
        auto rv = navigate(idx + 1, path, *cur_item.subitems[path[idx]], mod);
        return {rv.first, rv.second | false};
    } else {
        if (mod) {
            // cout << "MAKING " << path[idx] << ' ' << idx << " == " << path.size() - 1 << '\n';
            cur_item.subitems[path[idx]] = new Item({path[idx], 0, idx == path.size() - 1});
            // cout << "TESTING\n";
            // cur_item.subitems[path[idx]]->print();
            auto rv = navigate(idx + 1, path, *cur_item.subitems[path[idx]], mod);
            return {rv.first, rv.second | true};
        } else {
            return {nullptr, false};
        }
    }
    assert(false);
}

string add_file(vector<string> query, Item &root) {
    auto path = get_path(query[1]);
    auto [it, ok] = navigate(0, path, root, true);
    if (ok) {
        it->sz = stoll(query[2]);
        return "true";
    } else {
        return "false";
    }
}

// returns {"", "-1"} if not found
pair<string, string> get_file(vector<string> query, Item &root) {
    auto path = get_path(query[1]);
    auto [it, ignore] = navigate(0, path, root);
    if (it == nullptr) {
        return {"", ""};
    } else {
        return {it->name, to_string(it->sz)};
    }
}

string copy_file(vector<string> query, Item &root) {
    auto path_s = get_path(query[1]);
    auto [it_s, ok_s] = navigate(0, path_s, root);
    // cout << "DEBUGGING\n";
    // it_s->print();
    if (it_s == nullptr || !it_s->is_file) {
        return "false";
    }
    return add_file({"ADD_FILE", query[2], to_string(it_s->sz)}, root);
}

string get_file_size(vector<string> query, Item &root) {
    auto file = get_file(query, root);
    return file.second;
}

vector<string> solution(vector<vector<string>> queries) {
    Item root; // just for not counting root as file..
    // cout << root.name << ' ' << root.subitems.size() << ' ' << root.files.size();
    root.print();
    vector<string> rv;
    for (auto &query : queries) {
        // auto decomp = get_path(query[1]);
        // cout << query[1] << '\n';
        // for (auto &tmp : decomp) {
        //     cout << tmp << ' ';
        // }
        // cout << '\n';
        if (query[0] == "ADD_FILE") {
            rv.push_back(add_file(query, root));
        } else if (query[0] == "COPY_FILE") {
            rv.push_back(copy_file(query, root));
        } else if (query[0] == "GET_FILE_SIZE") {
            rv.push_back(get_file_size(query, root));
        }
        root.print();
        cout << '\n';
    }
    return rv;
}
