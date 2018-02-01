#include <bits/stdc++.h>

using namespace std;

int n, x;

int main() {
    scanf("%d %d", &n, &x);
    int aux = x, initial = x;

    while (1) {
        if (n % 2 == 0) {
            if (aux == 2) aux = 1;
            else if (aux == 1) aux = 2;
        }
        else {
            if (aux == 1) aux = 0;
            else if (aux == 0) aux = 1;
        }

        n--;
        if (n == 0) break;
        else if (aux != 1 && aux != initial) break;
    }

    if (n > 0) {
        if (n % 6 == 2 || n % 6 == 5) aux = 1;
        else if (n % 6 == 3 || n % 6 == 4) aux = 2 - aux;
    }
    printf("%d\n", aux);
    return 0;
}
