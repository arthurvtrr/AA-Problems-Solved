#include <stdio.h>
#include <algorithm>
#include <string>
#include <iostream>
#include <map>

using namespace std;

string s;
map < char, int > cost;
bool reached[55][5050];

int main() {
    cost['I'] = 1;
    cost['V'] = 5;
    cost['X'] = 10;
    cost['L'] = 50;
    cost['C'] = 100;

    int t = 1;

    while (1) {
        cin >> s;
        if (s == "0") break;

        for (int i = 0; i < 55; i++)
            for (int j = 0; j < 5050; j++)
                reached[i][j] = 0;

        int siz = s.size();
        for (int i = 0; i < siz; i++) {
            int atual = cost[s[i]];
            if (i == 0) reached[i][atual] = true;
            else {
                for (int j = i-1; j >= 0; j--) {
                    for (int k = 0; k < 5050; k++) {
                        if (reached[j][k]) {
                            if (k >= atual) reached[i][atual+k] = true;
                            else reached[i][atual-k] = true;
                        }
                    }
                    if (cost[s[j]] >= atual) atual += cost[s[j]];
                    else atual -= cost[s[j]];
                }
            }
        }

        printf("Case %d:", t++);
        for (int i = 0; i < 5050; i++)
            if (reached[siz-1][i])
                printf(" %d", i);

        printf("\n");
    }
    return 0;
}
