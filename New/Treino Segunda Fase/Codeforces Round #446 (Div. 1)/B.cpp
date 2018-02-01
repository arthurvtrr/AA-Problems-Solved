#include <bits/stdc++.h>

using namespace std;

int n, nums[25], aux[25];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
        aux[i] = nums[i];
    }
    sort(aux, aux+n);

    for (int i = 0; i < n; i++) {
        int ind = -1;
        for (int j = 0; j < n; j++)
            if (aux[j] > nums[i])
                if (ind == -1 || aux[j] < aux[ind])
                    ind = j;

        if (ind == -1) nums[i] = aux[0];
        else nums[i] = aux[ind];
    }

    for (int i = 0; i < n; i++) {
        if (i) printf(" ");
        printf("%d", nums[i]);
    }
    printf("\n");

    return 0;
}
