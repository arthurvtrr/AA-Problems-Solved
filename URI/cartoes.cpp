#include <stdio.h>
#include <algorithm>

using namespace std;

int main() {
    int n, nums[11000];
    while(scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; i++)
            scanf("%d", &nums[i]);

        int sum = 0, a = 0, b = n-1;
        while (a < b) {
            if (nums[a] > nums[b]) {
                sum += nums[a++];
                if (nums[a] < nums[b]) a++;
                else b--;
            }
            else {
                sum += nums[b--];
                if (nums[a] < nums[b]) a++;
                else b--;
            }
        }
        printf("%d\n", sum);
    }
}
