#include <bits/stdc++.h>

using namespace std;

int n, m;
long long numsT[100100], auxT[100100], numsB[100100], auxB[100100];

int main() {
    int t = 1;
    while (scanf("%d %d", &n, &m) != EOF) {
        for (int i = 0; i < n; i++) {
            scanf("%lld", &numsT[i]);
            auxT[i] = numsT[i];
        }
        for (int i = 0; i < m; i++) {
            scanf("%lld", &numsB[i]);
            auxB[i] = numsB[i];
        }

        sort(numsT, numsT+n);
        sort(auxT, auxT+n);
        sort(numsB, numsB+m);
        sort(auxB, auxB+m);

        int post = n-1, posb = m-1, player = 0;
        while (post >= 0 && posb >= 0) {
            if (player == 0) {
                if (numsT[post] > numsB[posb]) posb--;
                else {
                    if (post > 0)
                        numsT[post-1] += numsT[post];
                    post--;
                }
                player = 1;
            }
            else {
                if (numsB[posb] > numsT[post]) post--;
                else {
                    if (posb > 0)
                        numsB[posb-1] += numsB[posb];
                    posb--;
                }
                player = 0;
            }
        }

        printf("Case %d: ", t++);
        if (post >= 0) printf("Takeover Incorporated\n");
        else {
            post = n-1, posb = m-1, player = 0;
            bool first = false;
            while (post >= 0 && posb >= 0) {
                if (player == 0) {
                    if (auxT[post] > auxB[posb] && first) posb--;
                    else {
                        if (post > 0)
                            auxT[post-1] += auxT[post];
                        post--;
                    }
                    player = 1;
                }
                else {
                    if (auxB[posb] > auxT[post]) post--;
                    else {
                        if (posb > 0)
                            auxB[posb-1] += auxB[posb];
                        posb--;
                    }
                    player = 0;
                }
                first = true;
            }

            if (post >= 0) printf("Takeover Incorporated\n");
            else printf("Buyout Limited\n");
        }
    }

    return 0;
}

