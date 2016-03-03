#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    int m, s;
    scanf("%d %d", &m, &s);
    string s1 = "1", s2 = "1";

    if (m == 1 && s == 0) printf("0 0\n");
    else if (s == 0) printf("-1 -1\n");
    else if (1.0 * s / m > 9) printf("-1 -1\n");
    else {
        for (int i = 1; i < m; i++) {
            s1 += '0';
            s2 += '0';
        }

        int x = 1;
        for (int i = m-1; i >= 0; i--) {
            for (int j = 0; j < (i == 0? 8 : 9); j++) {
                if (x == s) break;
                s1[i]++;
                x++;
            }
            if (x == s) break;
        }

        x = 1;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < (i == 0? 8 : 9); j++) {
                if (x == s) break;
                s2[i]++;
                x++;
            }
            if (x == s) break;
        }

        cout << s1 << " " << s2 << endl;
    }
    return 0;
}
