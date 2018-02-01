#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <math.h>
#include <vector>

using namespace std;

string s;

int main() {
    cin >> s;

    int siz = s.size(), weight = 1, n = siz / 3;

    for (int i = 0; i < siz - 1; i++)
        if (s[i] != s[i+1]) weight++;

    vector < int > used;

    for (int i = 1; i < siz - 2; i++) {
        if (weight >= 2*n) break;

        if (s[i-1] == s[i] && s[i+1] == s[i+2]) {
            if (s[i] == '1') s[i] = '0';
            else s[i] = '1';

            if (s[i+1] == '1') s[i+1] = '0';
            else s[i+1] = '1';

            weight += 2;
            used.push_back(i+1);
        }
    }

    if (weight < 2*n && s[1] == s[2]) {
        if (s[0] == '1') s[0] = '0';
        else s[0] = '1';

        if (s[1] == '1') s[1] = '0';
        else s[1] = '1';

        weight++;
        used.push_back(1);
    }

    if (weight < 2*n && s[siz-2] == s[siz-3]) {
        if (s[siz-1] == '1') s[siz-1] = '0';
        else s[siz-1] = '1';

        if (s[siz-2] == '1') s[siz-2] = '0';
        else s[siz-2] = '1';

        weight++;
        used.push_back(siz-1);
    }

    printf("%d\n", used.size());
    for (int i = 0; i < used.size(); i++) {
        if (i > 0) printf(" ");
        printf("%d", used[i]);
    }
    printf("\n");

    return 0;
}
