#include <bits/stdc++.h>

using namespace std;

int k;

int main() {
    scanf("%d", &k);
    int cont = 0;
    for (int i = 1; i < 100000; i++) {
        int last = 0, aux = i;
        bool valid = true;

        while (aux) {
            int x = aux & 1;
            if (x == 1 && last == 1) valid = false;
            last = x;
            aux >>= 1;
        }

        if (valid) cont++;
        if (cont == k) {
            printf("%d\n", i);
            break;
        }
    }

    return 0;
}

