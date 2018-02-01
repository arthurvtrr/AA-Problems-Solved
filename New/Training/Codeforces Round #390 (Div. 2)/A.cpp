#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

int n, nums[110];

int main() {
    scanf("%d", &n);

    int sum = 0, dif = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
        sum += nums[i];
        if (nums[i] != 0) dif++;
    }

    if (dif == 0) printf("NO\n");
    else if (sum != 0) printf("YES\n1\n1 %d\n", n);
    else {
        int pos = n-1, s = 0;
        while (s == 0) {
            s += nums[pos];
            pos--;
        }
        printf("YES\n2\n");
        printf("1 %d\n", pos+1);
        printf("%d %d\n", pos+2, n);
    }
    return 0;
}
