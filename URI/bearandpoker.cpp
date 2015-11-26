#include <stdio.h>

using namespace std;

int nums[110000];

int gcd(int a, int b) {
    return (b == 0? a : gcd(b, a % b));
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);

    int x = nums[0];
    for (int i = 1; i < n; i++)
        x = gcd(x, nums[i]);

    while (x % 2 == 0) x /= 2;
    while (x % 3 == 0) x /= 3;

    bool f = true;
    for (int i = 0; i < n; i++) {
        int a = 1, b = 1;
        while (nums[i] % (a * 2) == 0) a *= 2;
        while (nums[i] % (b * 3) == 0) b *= 3;
        if (x * a * b != nums[i]) f = false;
    }

    if (f) printf("Yes\n");
    else printf("No\n");

    return 0;
}
