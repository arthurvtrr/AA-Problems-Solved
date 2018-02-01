#include <bits/stdc++.h>

using namespace std;

int l, r, x, y, k;

int main() {
    scanf("%d %d %d %d %d", &l, &r, &x, &y, &k);
    bool valid = false;
    for (int i = l; i <= r; i++)
        if (i % k == 0 && i/k >= x && i/k <= y)
            valid = true;
    if (valid) printf("YES\n");
    else printf("NO\n");

    return 0;
}
