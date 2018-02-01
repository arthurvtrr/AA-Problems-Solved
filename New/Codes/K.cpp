#include <stdio.h>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

int t, n, p, mod[1000100];
unsigned long long a, b;

int main() {
    scanf("%d", &t);

    while (t--) {
        scanf("%llu %llu %d %d", &a, &b, &n, &p);

        string s = "";

        while (s.size() < n) {
            a *= 10;
            s += (a / b) + '0';
            a -= (a / b) * b;
        }

        mod[0] = 0;
        for (int i = 1; i <= n; i++) {
            mod[i] = mod[i-1] * 10;
            mod[i] += s[i-1] - '0';
            mod[i] %= p;
        }

        long long sol = 0;

        for (int i = 0; i < p; i++) {
            long long cont = 0;

            for (int j = n; j > 0; j--) {
                if (mod[j] == i)
                    cont++;

                if (i == 0 && ((s[j-1] - '0') == mod[j] || mod[j] == i)) sol += cont;
                else if (mod[j] == i) sol += max(0LL, cont-1);
            }
        }

        printf("%lld\n", sol);
    }
    return 0;
}
