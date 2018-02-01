#include <bits/stdc++.h>

using namespace std;

int n, x;

int main() {
    scanf("%d %d", &n, &x);

    if (n == 1) {
        printf("YES\n%d\n", x);
    }
    else if (n == 2) {
        if (x == 0) printf("NO\n");
        else printf("YES\n0 %d\n", x);
    }
    else {
        vector < int > nums;
        int val = 0;
        for (int i = 1; i <= n - 3; i++) {
            nums.push_back(i);
            val ^= i;
        }
        nums.push_back(1 << 17);
        nums.push_back(1 << 18);
        val ^= 1 << 17;
        val ^= 1 << 18;

        nums.push_back(val ^ x);

        printf("YES\n");
        for (int i = 0; i < nums.size(); i++) {
            if (i) printf(" ");
            printf("%d", nums[i]);
        }
        printf("\n");
    }

    return 0;
}

