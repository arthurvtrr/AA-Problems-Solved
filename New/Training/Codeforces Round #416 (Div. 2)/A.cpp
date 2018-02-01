#include <bits/stdc++.h>

using namespace std;

#define ll long long

ll a, b;

int main() {
    scanf("%lld %lld", &a, &b);
    int rem = 1;
    while (1) {
        if (rem % 2 && a < rem) { printf("Vladik\n"); break; }
        else if (rem % 2) a -= rem;
        else if (rem % 2 == 0 && b < rem) { printf("Valera\n"); break; }
        else b -= rem;

        rem++;
    }
    return 0;
}
