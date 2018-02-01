#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

int n, cs[200200], divs[200200];

int main() {
    scanf("%d", &n);

    bool div2 = false;
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &cs[i], &divs[i]);
        if (divs[i] == 2) div2 = true;
    }

    if (!div2) printf("Infinity\n");
    else {
        int d = divs[0], ini, fim;

        if (d == 2) {
            ini = -300000000, fim = 1899;
        }
        else {
            ini = 1900, fim = 300000000;
        }

        while (ini <= fim) {
            int meio = (ini + fim) / 2;
            int aux = meio;

            bool valid = true;

            for (int i = 1; i < n; i++) {
                meio += cs[i-1];
                if (divs[i] == 2 && meio >= 1900) {
                    fim = aux-1;
                    valid = false;
                    break;
                }
                else if (divs[i] == 1 && meio < 1900) {
                    ini = aux+1;
                    valid = false;
                    break;
                }
            }

            if (valid) ini = aux+1;
        }

        bool possible = true;

        ini--;
        if (divs[0] == 1 && ini < 1900) possible = false;
        else if (divs[0] == 2 && ini >= 1900) possible = false;

        for (int i = 1; i < n; i++) {
            ini += cs[i-1];
            if (divs[i] == 2 && ini >= 1900) {
                possible = false;
            }
            else if (divs[i] == 1 && ini < 1900) {
                possible = false;
            }
        }

        if (!possible) printf("Impossible\n");
        else printf("%d\n", ini + cs[n-1]);
    }

    return 0;
}

