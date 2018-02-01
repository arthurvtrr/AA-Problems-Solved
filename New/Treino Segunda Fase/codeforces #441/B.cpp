#include <bits/stdc++.h>

using namespace std;

int n, mv[300300];
bool pos[300300];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &mv[i]);

    printf("1");

    int lst = n;
    for (int i = 0; i < n; i++) {
        pos[mv[i]] = true;
        while (lst >= 0 && pos[lst]) lst--;
        printf(" %d", (i+1) - (n - lst) + 1);
    }
    printf("\n");

    return 0;
}

