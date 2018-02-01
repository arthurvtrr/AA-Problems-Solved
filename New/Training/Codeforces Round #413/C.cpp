#include <bits/stdc++.h>

using namespace std;

#define pii pair < int, int >

int n, c, d;

struct fountain {
    int b, p;
    char t;
} fountains[100100];

bool cmp(fountain a, fountain b) {
    return a.p < b.p;
}

vector < pii > coin, diam;
int maxi[2][100100];

int main() {
    scanf("%d %d %d", &n, &c, &d);
    for (int i = 0; i < n; i++)
        scanf("%d %d %c", &fountains[i].b, &fountains[i].p, &fountains[i].t);
    sort(fountains, fountains+n, cmp);

    for (int i = 0; i < n; i++) {
        if (fountains[i].t == 'C') coin.push_back(pii(fountains[i].b, fountains[i].p));
        else diam.push_back(pii(fountains[i].b, fountains[i].p));
    }

    int atual = 0;
    for (int i = 0; i < coin.size(); i++) {
        atual = max(atual, coin[i].first);
        maxi[0][i] = atual;
    }

    atual = 0;
    for (int i = 0; i < diam.size(); i++) {
        atual = max(atual, diam[i].first);
        maxi[1][i] = atual;
    }

    int ans = 0, maxc = 0, maxd = 0;

    for (int i = 0; i < coin.size(); i++)
        if (coin[i].second <= c) maxc = max(maxc, coin[i].first);
    for (int i = 0; i < diam.size(); i++)
        if (diam[i].second <= d) maxd = max(maxd, diam[i].first);
    if (maxc > 0 && maxd > 0)
        ans = maxc + maxd;

    for (int i = 1; i < coin.size(); i++)
        if (coin[i].second < c) {
            int aux = coin[i].first, left = c - coin[i].second;
            int ini = 0, fim = i-1;
            while (ini <= fim) {
                int mid = (ini + fim) / 2;
                if (coin[mid].second <= left) ini = mid+1;
                else fim = mid-1;
            }
            if (fim >= 0) {
                aux += maxi[0][fim];
                ans = max(ans, aux);
            }
        }

    for (int i = 1; i < diam.size(); i++)
        if (diam[i].second < d) {
            int aux = diam[i].first, left = d - diam[i].second;
            int ini = 0, fim = i-1;
            while (ini <= fim) {
                int mid = (ini + fim) / 2;
                if (diam[mid].second <= left) ini = mid+1;
                else fim = mid-1;
            }
            if (fim >= 0) {
                aux += maxi[1][fim];
                ans = max(ans, aux);
            }
        }

    printf("%d\n", ans);

    return 0;
}

