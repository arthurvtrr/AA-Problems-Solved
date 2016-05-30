#include <stdio.h>
#include <algorithm>

using namespace std;

long long nums[110], x, cont_0[110];

int main() {
    while (scanf("%lld", &nums[1]) != EOF) {

        for (int i = 0; i < 110; i++) {
            if (i != 1) nums[i] = 1;
            cont_0[i] = 0;
        }

        int pos = 2;
        while (1) {
            scanf("%lld", &x);
            if (x == -999999) break;
            nums[pos++] = x;
        }

        for (int i = 1; i < pos; i++) {
            if (nums[i] == 0) {
                cont_0[i]++;
                nums[i] = 1;
            }
            cont_0[i] += cont_0[i-1];
            nums[i] *= nums[i-1];
        }

        long long sol = -99999999999, aux;
        for (int i = 1; i < pos; i++)
            for (int j = i; j < pos; j++) {
                if (cont_0[j] - cont_0[i-1] > 0) aux = 0;
                else aux = nums[j] / nums[i-1];
                sol = max(sol, aux);
            }

        printf("%lld\n", sol);
    }

    return 0;
}
