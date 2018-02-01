#include <bits/stdc++.h>

using namespace std;

int n, x, m, a, b;
bool inv[100100];

int main() {
    scanf("%d", &n);
    int sum = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        sum += x;
    }
    int mini = 0;

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        for (int j = a; j <= b; j++)
            inv[j] = true;
    }

    for (int i = 0; i < 100100; i++)
        if (inv[i] && i >= sum) {
            mini = i;
            break;
        }

    if (mini != 0) printf("%d\n", mini);
    else printf("-1\n");

    return 0;
}
