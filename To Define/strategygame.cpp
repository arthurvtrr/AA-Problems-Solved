#include <stdio.h>
#include <algorithm>

using namespace std;

int main() {
    int J, r, points[550], x;
    while(scanf("%d %d", &J, &r) != EOF) {
        for (int i = 0; i < 550; i++) points[i] = 0;

        for (int i = 0; i < r; i++) {
            for (int j = 0; j < J; j++) {
                scanf("%d", &x);
                points[j+1] += x;
            }
        }

        int sol = 1;
        for (int i = 2; i <= J; i++)
            if (points[i] >= points[sol]) sol = i;

        printf("%d\n", sol);
    }
    return 0;
}
