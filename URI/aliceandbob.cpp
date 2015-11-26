#include <stdio.h>

using namespace std;

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    int n, nums[110], mx = -1, odd = 0;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
        if (nums[i] > mx) mx = nums[i];
    }

    int div = nums[0];
    for (int i = 1; i < n; i++)
        div = gcd(div, nums[i]);

    if ((mx / div - n) % 2 == 0) printf("Bob\n");
    else printf("Alice\n");

    return 0;
}
