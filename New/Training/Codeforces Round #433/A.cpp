#include <bits/stdc++.h>

using namespace std;

int n;

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    scanf("%d", &n);
    int last = 1;
    for (int i = 2; i < n; i++) {
        int dem = n - i;
        if (i < dem && gcd(i, dem) == 1)
            last = i;
    }

    printf("%d %d\n", last, n - last);

    return 0;
}
