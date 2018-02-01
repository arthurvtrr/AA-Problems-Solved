#include <stdio.h>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

int n, m, nums[55][55];

int main() {
    while(scanf("%d %d", &n, &m) != EOF) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                scanf("%d", &nums[i][j]);

        int maximum = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)

        printf("%d\n", maximum);
    }
    return 0;
}

