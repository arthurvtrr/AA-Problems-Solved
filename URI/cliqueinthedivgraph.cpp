#include <stdio.h>

using namespace std;

bool visited[1100000];

int main() {
    int n, nums[1100000], maxv = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
        if (maxv < nums[i])
            maxv = nums[i];
        visited[nums[i]] = true;
    }

    int max_clique = 0;
    for (int i = 0; i < maxv+1; i++) {
        if (visited[i]) {
            int clique = 1;
            for (int j = i+i; j < maxv+1; j += i)
                if (visited[j]) {
                    clique++;
                    visited[j] = false;
                }
            if (clique > max_clique)
                max_clique = clique;
        }
    }

    printf("%d\n", max_clique);
    return 0;
}
