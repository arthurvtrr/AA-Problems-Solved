#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>

using namespace std;

int n;

int main() {
    scanf("%d", &n);

    if (n % 2 == 0) {
        printf("%d\n", n / 2);
        for (int i = 0; i < n/2; i++) {
            if (i > 0) printf(" ");
            printf("2");
        }
        printf("\n");
    }
    else {
        vector < int > nums;
        n -= 3;
        nums.push_back(3);
        while (n > 0) {
            n -= 2;
            nums.push_back(2);
        }

        printf("%d\n", nums.size());
        for (int i = 0; i < nums.size(); i++) {
            if (i > 0) printf(" ");
            printf("%d", nums[i]);
        }
        printf("\n");
    }
    return 0;
}
