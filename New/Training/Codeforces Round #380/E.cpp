#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

int n, s;
int nums[200200], cont[200200];

int main() {
    scanf("%d %d", &n, &s);

    int sol = 0;

    for (int i = 1; i <= n; i++) {
        scanf("%d", &nums[i]);
        if (i == s && nums[i] != 0) {
            nums[i] = 0;
            sol++;
        }
    }

    for (int i = 1; i <= n; i++)
        cont[nums[i]]++;

    int atual = 1, last = n-1;
    while (1) {
        if (cont[0] == 1) break;

        if (cont[atual] == 0) {
            cont[0]--;
            sol++;
        }
        atual++;
    }

    while (1) {
        while (cont[last] == 0) last--;
        if (atual >= last) break;

        if (cont[atual] == 0) {
            cont[last]--;
            sol++;
        }
        atual++;
    }

    printf("%d\n", sol);

    return 0;
}

