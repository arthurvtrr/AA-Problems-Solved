#include <bits/stdc++.h>

using namespace std;

int n;

int main() {
    scanf("%d", &n);
    if (n % 2 == 0) printf("%d\n", n / 2 - 1);
    else printf("%d\n", n / 2);
    return 0;
}
