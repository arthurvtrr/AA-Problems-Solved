#include <stdio.h>
#include <algorithm>

using namespace std;

int n, m;
int nums[20], fim[20];
bool p;

void possible(int siz, int arr[]) {
    if (siz == m) {
        bool eq1 = true, eq2 = true;
        for (int i = 0; i < siz; i++) {
            if (arr[i] != fim[i])
                eq1 = false;
            if (arr[siz-i-1] != fim[i])
                eq2 = false;
        }
        if (eq1 || eq2) p = true;
    }
    else if (siz < m) return;
    else {
        int aux[siz];
        for (int i = 0; i < siz-1; i++) {
            for (int j = siz-1; j >= 0; j--) {
                if (j > i) aux[j] = 0;
                else aux[j] = arr[i-j];
            }
            int c = 0;
            for (int j = i+1; j < siz; j++)
                aux[c++] += arr[j];
            possible(max(c, i+1), aux);
        }
    }
}

int main() {
    while (scanf("%d", &n) != EOF) {
        p = false;
        for (int i = 0; i < n; i++)
            scanf("%d", &nums[i]);
        scanf("%d", &m);
        for (int i = 0; i < m; i++)
            scanf("%d", &fim[i]);

        possible(n, nums);
        if (p) printf("S\n");
        else printf("N\n");
    }
    return 0;
}
