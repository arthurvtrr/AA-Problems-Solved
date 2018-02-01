#include <bits/stdc++.h>

using namespace std;

int n, x;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        bool v = false;
        for (int j = 0; j < 100; j++)
            if (x >= j*3)
                if ((x - j*3) % 7 == 0)
                    v = true;

        if (v) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
