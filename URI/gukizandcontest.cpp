#include <stdio.h>

using namespace std;

int main() {
    int n, ratings[2200], positions[2200];
    for (int i = 0; i < 2200; i++)
        positions[i] = 0;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d", &ratings[i]);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            if (ratings[i] < ratings[j])
                positions[i]++;
        printf("%d", positions[i] + 1);
        if (i < n - 1) printf(" ");
    }
    printf("\n");

    return 0;
}
