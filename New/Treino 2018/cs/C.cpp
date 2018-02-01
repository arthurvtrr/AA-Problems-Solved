#include <bits/stdc++.h>

using namespace std;

int n, x;

int main() {
    scanf("%d", &n);
    for (int i = 2; i < n; i++) {
        printf("Q %d %d\n", 1, i);
        fflush(stdout);
        scanf("%d", &x);
    }
    printf("A\n");
    fflush(stdout);

    return 0;
}
