#include <bits/stdc++.h>

using namespace std;

int a, b, c, d, x, y;

int main() {
    scanf("%d %d %d %d", &a, &b, &c, &d);
    scanf("%d %d", &x, &y);

    if (abs(a-c) % x == 0 && abs(b-d) % y == 0 && abs(abs(a-c) / x - abs(b-d) / y) % 2 == 0) printf("YES\n");
    else printf("NO\n");


    return 0;
}
