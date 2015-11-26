#include <stdio.h>

using namespace std;

int main() {
    int n, m, vals[1100], sol = 0, x, y;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++)
        scanf("%d", &vals[i+1]);

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        if (vals[x] < vals[y]) sol += vals[x];
        else sol += vals[y];
    }

    printf("%d\n", sol);
    return 0;
}
