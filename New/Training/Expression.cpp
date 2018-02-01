#include <bits/stdc++.h>

using namespace std;

int a, b, c;

int main() {
    scanf("%d %d %d", &a, &b, &c);

    int ans = 0;
    ans = max({ans, a+b+c, a+b*c, a*b+c, a*c*b, (a+b)*c, a*(b+c)});
    printf("%d\n", ans);

    return 0;
}
