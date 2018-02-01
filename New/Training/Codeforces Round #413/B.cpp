#include <bits/stdc++.h>

using namespace std;

#define pii pair < int, int >

int n, m, c, p[200200], a[200200], b[200200];
set < pii > prices[4];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &p[i]);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    for (int i = 0; i < n; i++)
        scanf("%d", &b[i]);

    for (int i = 0; i < n; i++) {
        prices[a[i]].insert(pii(p[i], i));
        prices[b[i]].insert(pii(p[i], i));
    }

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &c);
        if (i) printf(" ");

        if (prices[c].empty()) printf("-1");
        else {
            pii aux = *prices[c].begin();

            printf("%d", aux.first);
            prices[a[aux.second]].erase(aux);
            prices[b[aux.second]].erase(aux);
        }
    }
    printf("\n");

    return 0;
}

