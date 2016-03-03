#include <stdio.h>
#include <algorithm>

using namespace std;

int main() {
    int n, sol = 0;
    char x[1100], y[1100];
    scanf("%d", &n);
    scanf("%s %s", x, y);

    for (int i = 0; i < n; i++) {
        int a = x[i] - '0', b = y[i] - '0';
        sol += min(abs(a-b), 9 - max(a,b) + min(a,b) + 1);
    }

    printf("%d\n", sol);
    return 0;
}
