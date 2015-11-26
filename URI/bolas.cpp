#include <stdio.h>
#include <algorithm>

using namespace std;

struct cor {
    int cor;
    int q;
} cores[15];

bool comp(cor a, cor b) {
    return a.q < b.q;
}

int main() {
    int h, w, c;
    int tab[15][15];
    while (1) {
        scanf("%d %d %d", &h, &w, &c);
        if (h == 0 && w == 0 && c == 0) break;

        for (int i = 0; i < c; i++) {
            scanf("%d", &cores[i].q);
            cores[i].cor = i+1;
        }

        sort(cores, cores+c, comp);

        int i = 0;
        for (int col = 0; col < w; col++) {
            for (int lin = 0; lin < h; lin++) {
                while (cores[i].q == 0) i++;
                tab[lin][col] = cores[i].cor;
                cores[i].q--;
            }
        }

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++)
                printf("%d", tab[i][j]);
            printf("\n");
        }

    }
    return 0;
}
