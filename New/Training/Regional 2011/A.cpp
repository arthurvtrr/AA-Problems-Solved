#include <bits/stdc++.h>

using namespace std;

int d;
string n;

int main() {
    while (1) {
        cin >> d >> n;
        if (d == 0 && n == "0") break;

        string ans = "";
        for (int i = 0; i < n.size(); i++)
            if (n[i] - '0' != d)
                ans += n[i];

        int i = 0;
        while (i + 1 < ans.size() && ans[i] == '0') i++;

        for (i; i < ans.size(); i++)
            printf("%c", ans[i]);

        if (ans.size() == 0) printf("0");
        printf("\n");
    }

    return 0;
}
