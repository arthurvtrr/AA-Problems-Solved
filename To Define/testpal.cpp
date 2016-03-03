#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

int nums[2200];
int L[2200][2200];

int LPS(char* str, int a, int b) {
    if (a == b)
        return nums[a]? 3000 : 1;

    if (a + 1 == b) {
        if (str[a] == str[b])
            return (nums[a]? 3000 : 1) + (nums[b]? 3000 : 1);
        else
            return nums[a] || nums[b]? 3000 : 1;
    }

    if (L[a][b] == -1) {
        if (str[a] == str[b])
            L[a][b] = (nums[a]? 3000 : 1) + (nums[b]? 3000 : 1) + LPS(str, a+1, b-1);

        L[a][b] = max(L[a][b], LPS(str, a, b-1));
        L[a][b] = max(L[a][b], LPS(str, a+1, b));
    }
    return L[a][b];
}

int main() {
    char s[2200];
    int n, x;
    while (scanf("%s", s) != EOF) {
        for (int i = 0; i < 2200; i++) {
            nums[i] = 0;
            for (int j = 0; j < 2200; j++)
                L[i][j] = -1;
        }

        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &x);
            nums[x-1]++;
        }

        for (int i = 0; i < strlen(s); i++)
            L[i][i] = nums[i];

        int aux = LPS(s, 0, strlen(s)-1);
        int sol = (aux / 3000) + (aux % 3000);
        printf("%d\n", sol);
    }
    return 0;
}

