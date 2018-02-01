#include <bits/stdc++.h>

using namespace std;

int parts[10][10];

int main() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            scanf("%d", &parts[i][j]);

    bool acc = false;
    for (int i = 0; i < 4; i++) {
        if (parts[i][3] == 0) continue;

        for (int j = 0; j < 3; j++)
            if (parts[i][j] == 1) acc = true;

        for (int j = 1; j < 4; j++)
            if (parts[(i+j)%4][j-1] == 1) acc = true;
    }

    if (acc) printf("YES\n");
    else printf("NO\n");

    return 0;
}
