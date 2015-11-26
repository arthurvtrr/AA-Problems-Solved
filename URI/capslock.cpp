#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    cin >> s;
    bool to_change = true;
    for (int i = 1; i < s.size(); i++)
        if (islower(s[i]))
            to_change = false;

    if (to_change) {
        if (islower(s[0])) s[0] -= 32;
        else s[0] += 32;

        for (int i = 1; i < s.size(); i++)
            s[i] += 32;
    }

    cout << s << endl;
}
