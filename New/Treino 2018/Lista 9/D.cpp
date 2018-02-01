#include <bits/stdc++.h>

using namespace std;

int n, k, nums[110];

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);

    int a = 1000, b = 1;
    vector < int > ans;

    for (int i = 0; i < n; i++)
        for (int j = 1; j <= k; j++) {
            int x = nums[i], y = j;
            bool val = true;
            vector < int > aux;

            for (int l = 0; l < n; l++) {
                int ini = 1, fim = k;
                while (ini <= fim) {
                    int meio = (ini + fim) / 2;
                    if (nums[l] * j <= nums[i] * meio) fim = meio-1;
                    else ini = meio+1;
                }
                if (ini > k) {
                    val = false;
                    break;
                }
                aux.push_back(ini);
                if (nums[l] * y < x * ini) {
                    x = nums[l];
                    y = ini;
                }
            }

            if (!val) continue;

            int num = nums[i] * y, den = j * x;
            if (num * b < a * den) {
                a = num;
                b = den;
                ans = aux;
            }
        }

    for (int i = 0; i < n; i++) {
        if (i) printf(" ");
        printf("%d", ans[i]);
    }
    printf("\n");

    return 0;
}
