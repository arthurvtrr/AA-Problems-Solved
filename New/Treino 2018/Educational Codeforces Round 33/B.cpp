#include <bits/stdc++.h>

using namespace std;

bool dv[10010000];
int n;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= sqrt(n) + 1; i++)
        if (n % i == 0)
            dv[i] = dv[n/i] = true;

    for (int i = 11; i >= 1; i--)
        if (dv[((1 << i) - 1)*(1 << (i-1))]) {
            printf("%d\n", ((1 << i) - 1)*(1 << (i-1)));
            break;
        }

    return 0;
}

