#include <bits/stdc++.h>

using namespace std;

string s;

int main() {
    cin >> s;

    vector < int > divs;
    int sqr = sqrt(s.size());
    for (int i = 1; i <= sqr; i++)
        if (s.size() % i == 0) {
            divs.push_back(i);
            divs.push_back(s.size() / i);
        }

    int mini = s.size();

    for (int i = 0; i < divs.size(); i++) {
        int div = divs[i];
        bool valid = true;
        for (int j = 0; j < div; j++) {
            char c = '?';
            for (int k = j; k < s.size(); k += div) {
                if (s[k] == '0' && c == '?') c = '0';
                else if (s[k] == '0' && c == '1') c = '2';
                else if (s[k] == '1' && c == '?') c = '1';
                else if (s[k] == '1' && c == '0') c = '2';
            }

            if (c == '2') valid = false;
        }
        if (valid) mini = min(mini, div);
    }

    string ans = s;
    for (int i = 0; i < mini; i++) {
        char c = '?';
        for (int k = i; k < s.size(); k += mini) {
            if (s[k] == '0' && c == '?') c = '0';
            else if (s[k] == '1' && c == '?') c = '1';
        }
        if (c == '?') c = '0';
        for (int k = i; k < s.size(); k += mini)
            ans[k] = c;
    }

    cout << ans << endl;

    return 0;
}

