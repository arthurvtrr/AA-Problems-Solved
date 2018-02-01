#include <bits/stdc++.h>

using namespace std;

int a, b;

int main() {
    scanf("%d %d", &a, &b);
    int ans = 0;
    while (a <= b) {
        ans++;
        a *= 3; b *= 2;
    }
    printf("%d\n", ans);

    return 0;
}
