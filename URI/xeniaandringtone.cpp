#include <stdio.h>

using namespace std;

int main() {
    int n, m, nums[110000];
    scanf("%d %d", &n, &m);

    long long sol = 0, past = 1;
    for (int i = 0; i < m; i++) {
        scanf("%d", &nums[i]);
        if (nums[i] > past) {
            sol += nums[i] - past;
            past = nums[i];
        } else if (nums[i] < past) {
            sol += n - past;
            sol += nums[i];
            past = nums[i];
        }
    }

    printf("%I64d\n", sol);

    return 0;
}
