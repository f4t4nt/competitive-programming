#include <bits/stdc++.h>

using namespace std;

class TextEditor {
private:
    string left, right;

public:
    TextEditor() {
    }
    
    void addText(string text) {
        for (char c : text) {
            left += c;
        }
    }
    
    int deleteText(int k) {
        int count = 0;
        while (k-- && !left.empty()) {
            left.pop_back();
            count++;
        }
        return count;
    }
    
    string getPreview(int len = 10) {
        len = min(len, (int) left.size());
        return left.substr(left.size() - len, len);
    }

    string cursorLeft(int k) {
        while (k-- && !left.empty()) {
            char c = left.back();
            left.pop_back();
            right += c;
        }
        return getPreview();
    }
    
    string cursorRight(int k) {
        while (k-- && !right.empty()) {
            char c = right.back();
            right.pop_back();
            left += c;
        }
        return getPreview();
    }
};

/**
 * Your TextEditor object will be instantiated and called as such:
 * TextEditor* obj = new TextEditor();
 * obj->addText(text);
 * int param_2 = obj->deleteText(k);
 * string param_3 = obj->cursorLeft(k);
 * string param_4 = obj->cursorRight(k);
 */