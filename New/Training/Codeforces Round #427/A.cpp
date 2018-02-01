#include <bits/stdc++.h>

using namespace std;

int s, a, b, c, d;

int main() {
    scanf("%d %d %d %d %d", &s, &a, &b, &c, &d);
    if (2*c + a*s < 2*d + b*s) printf("First\n");
    else if (2*c + a*s == 2*d + b*s) printf("Friendship\n");
    else printf("Second\n");

    return 0;
}
