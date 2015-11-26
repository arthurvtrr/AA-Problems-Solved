#include <bits/stdc++.h>

using namespace std;

int main() {
    string s;
    cin >> s;

    if (s.size() == 1 && (s[0] - '0') % 8 == 0) {
        printf("YES\n");
        cout << s << "\n";
    }
    else if (s.size() == 1) printf("NO\n");
    else if (s.size() == 2) {
        if (stoi(s) % 8 == 0) {
            printf("YES\n");
            cout << s;
        }
        else if ((s[0] - '0') % 8 == 0) {
            printf("YES\n");
            cout << s[0] << "\n";
        }
        else if ((s[1] - '0') % 8 == 0) {
            printf("YES\n");
            cout << s[1] << "\n";
        }
        else printf("NO\n");
    }
    else {
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
    }

    return 0;
}

