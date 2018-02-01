#include <bits/stdc++.h>

using namespace std;

int a, b, c, d;
set < int > scream;

int main() {
    scanf("%d %d %d %d", &a, &b, &c, &d);

    int ans = -1;
    for (int i = 0; i < 100000; i++)
        scream.insert(b + i*a);

    for (int i = 0; i < 100000; i++)
        if (scream.count(d + i*c)) {
            ans = d + i*c;
            break;
        }

    printf("%d\n", ans);

    return 0;
}
