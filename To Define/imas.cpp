#include <iostream>
#include <string.h>

using namespace std;

int let[300];

int main() {
    string s;
    while (1) {
        getline(cin, s);
        if (s == "FIM") break;

        memset(let, 0, sizeof let);
        for (char c : s)
            let[c]++;

        bool p = true;
        for (int i = 56; i < 300; i++)
            if (let[i] > 1)
                p = false;

        if (p) cout << s << "\n";
    }
    return 0;
}
