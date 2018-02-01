#include <bits/stdc++.h>

using namespace std;

int k[3];

int main() {
    scanf("%d %d %d", &k[0], &k[1], &k[2]);
    sort(k, k+3);

    bool valid = false;
    do {
        int pos = -1;
        for (int i = 1; i < 50000; i++)
            if (((i - 1) % k[0]) && ((i - 2) % k[1])) {
                pos = i;
                break;
            }

        if (pos == -1) { valid = true; break; }

        int lst = -1;
        for (int i = pos; i < 50000; i++)
            if (((i - 1) % k[0]) && ((i - 2) % k[1]) && ((i - pos) % k[2])) {
                lst = i;
                break;
            }

        if (lst == -1) { valid = true; break; }
    }
    while (next_permutation(k, k+3));

    if (valid) printf("YES\n");
    else printf("NO\n");

    return 0;
}
