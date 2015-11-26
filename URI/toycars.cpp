#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, col[110][110];
    vector < int > gcars;

    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &col[i][j]);

    for (int i = 1; i <= n; i++) {
        bool f = true;
        for (int j = 1; j <= n; j++)
            if (col[j][i] >= 2) f = false;
        if (f) gcars.push_back(i);
    }

    sort(gcars.begin(), gcars.end());

    printf("%d\n", gcars.size());
    for (int i = 0; i < gcars.size(); i++) {
        printf("%d", gcars[i]);
        if (i < gcars.size() - 1) printf(" ");
    }
    if (gcars.size() > 0) printf("\n");

    return 0;
}
