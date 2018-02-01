#include <bits/stdc++.h>

using namespace std;

int n, p, x;
set < int > levels;

int main() {
    scanf("%d", &n);
    scanf("%d", &p);
    for (int i = 0; i < p; i++) {
        scanf("%d", &x);
        levels.insert(x);
    }
    scanf("%d", &p);
    for (int i = 0; i < p; i++) {
        scanf("%d", &x);
        levels.insert(x);
    }

    if (levels.size() == n) printf("I become the guy.\n");
    else printf("Oh, my keyboard!\n");

    return 0;
}
