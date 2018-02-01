#include <bits/stdc++.h>

using namespace std;

long long b1, q, l, x;
int m;
set < long long > bad;

int main() {
    scanf("%lld %lld %lld %d", &b1, &q, &l, &m);

    for (int i = 0; i < m; i++) {
        scanf("%lld", &x);
        bad.insert(x);
    }

    if (b1 == 0) {
        if (bad.count(0)) printf("0\n");
        else printf("inf\n");
    }
    else if (q == 0) {
        int cont = 0;
        if (!bad.count(b1) && abs(b1) <= l) cont++;

        if (bad.count(0) || abs(b1) > l) printf("%d\n", cont);
        else printf("inf\n");
    }
    else if (q == 1) {
        if (bad.count(b1) || abs(b1) > l) printf("0\n");
        else printf("inf\n");
    }
    else if (q == -1) {
        if (abs(b1) > l || (bad.count(b1) && bad.count(-b1))) printf("0\n");
        else printf("inf\n");
    }
    else {
        int cont = 0;
        while (abs(b1) <= l) {
            if (!bad.count(b1)) cont++;
            b1 *= q;
        }
        printf("%d\n", cont);
    }

    return 0;
}

