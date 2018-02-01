#include <bits/stdc++.h>

using namespace std;

int n;
char grid[110][110];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int dist = abs(i - n/2);
        for (int j = 0; j < n; j++) {
            if (abs(j - n/2) <= n/2 - dist) printf("D");
            else printf("*");
        }
        printf("\n");
    }

    return 0;
}


