#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <algorithm>

using namespace std;

int main() {
    string s;
    cin >> s;

    for (int i = 0; i < s.size(); i++) {
        string sol = "";
        sol = s[i];
        if (stoi(sol) % 8 == 0) {
            printf("YES\n");
            cout << sol << "\n";
            exit(0);
        }
        for (int j = i+1; j < s.size(); j++) {
            sol = "";
            sol += s[i];
            sol += s[j];
            if (stoi(sol) % 8 == 0) {
                printf("YES\n");
                cout << sol << "\n";
                exit(0);
            }
            for (int k = j+1; k < s.size(); k++) {
                sol = "";
                sol += s[i];
                sol += s[j];
                sol += s[k];
                if (stoi(sol) % 8 == 0) {
                    printf("YES\n");
                    cout << sol << "\n";
                    exit(0);
                }
            }
        }
    }
    printf("NO\n");
    return 0;
}
