#include <bits/stdc++.h>

using namespace std;

int n, nums[1010];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);

    int ser = 0, dima = 0, ini = 0, fim = n-1, p = 1;
    while (ini <= fim) {
        if (nums[ini] > nums[fim]) {
            if (p == 1) ser += nums[ini];
            else dima += nums[ini];
            ini++;
            p = 1 - p;
        }
        else {
            if (p == 1) ser += nums[fim];
            else dima += nums[fim];
            fim--;
            p = 1 - p;
        }
    }

    printf("%d %d\n", ser, dima);

    return 0;
}
