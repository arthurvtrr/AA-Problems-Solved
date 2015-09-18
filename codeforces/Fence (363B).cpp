#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;

int n, k, a;
int fence[170000];
int difs[170000];

int main()
{
    scanf("%d %d", &n, &k);
    int sum = 0;

    for (int i = 0; i < n; i++) {
        scanf("%d", &a);
        sum += a;
        fence[i] = sum;
    }

    if (n == 1) {
        printf("1");
        exit(0);
    }

    difs[k-1] = fence[k-1];
    for (int i = k; i < n; i++) {
        difs[i] = fence[i] - fence[i-k];
    }

    int minimun = difs[k-1];
    int index = 1;

    for (int j = k-1; j < n; j++) {
        if (difs[j] < minimun) {
            minimun = difs[j];
            index = j-(k-1)+1;
        }
    }

    printf("%d", index);

    return 0;
}