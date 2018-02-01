#include <bits/stdc++.h>

using namespace std;

int n, x, a[1000100], b[1000100];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        a[x]++;
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        b[x]++;
    }

    int sum = 0;
    for (int i = 1; i < 1000100; i++) {
        int maxa = -1, maxb = -1;
        for (int j = i; j < 1000100; j += i) {
            if (a[j]) maxa = max(maxa, j);
            if (b[j]) maxb = max(maxb, j);
        }
        if (maxa != -1 && maxb != -1)
            sum = maxa + maxb;
    }

    printf("%d\n", sum);

    return 0;
}
