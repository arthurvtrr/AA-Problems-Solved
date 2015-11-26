#include <stdio.h>
#include <math.h>

using namespace std;

int main() {
    long long int n;

    while (1) {
        scanf("%lld", &n);
        if (n == 0) break;

        long long int root = sqrt(n);
        if (root * root == n) printf("yes\n");
        else printf("no\n");
    }

    return 0;
}
