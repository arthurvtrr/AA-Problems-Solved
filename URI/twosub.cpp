#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    cin >> s;

    bool ba = false, ab = false;
    for (int i = 0; i < s.size() - 1; i++) {
        if (s[i] == 'A' && s[i+1] == 'B' && !ab) {
            ab = true;
            i++;
        }
        else if (s[i] == 'B' && s[i+1] == 'A' && !ba) {
            ba = true;
            i++;
        }
    }

    if (ba && ab) printf("YES\n");
    else printf("NO\n");

    return 0;
}
