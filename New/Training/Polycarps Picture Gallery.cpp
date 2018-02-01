#include <bits/stdc++.h>

using namespace std;

int n, m, type[1010];

struct photo {
    int quant;
    int ind;
} photos[50];

bool cmp(photo a, photo b) {
    return a.quant > b.quant;
}

int main() {
    int total = 0;

    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &photos[i].quant);
        photos[i].ind = i+1;
        photos[i].quant = min(photos[i].quant, n / 2);
        total += photos[i].quant;
    }

    if (total < n) printf("-1\n");
    else {
        sort(photos, photos+m, cmp);

        int pos = 0, chosen = 0;
        for (int i = 0; i < m; i++) {
            while (photos[i].quant > 0 && chosen < n) {
                type[pos] = photos[i].ind;
                chosen++;
                photos[i].quant--;
                pos += 2;
                if (pos >= n) pos = 1;
            }
        }

        for (int i = 0; i < n; i++) {
            if (i) printf(" ");
            printf("%d", type[i]);
        }
        printf("\n");
    }
    return 0;
}
