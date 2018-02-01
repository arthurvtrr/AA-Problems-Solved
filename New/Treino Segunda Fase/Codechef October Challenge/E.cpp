#include <bits/stdc++.h>

using namespace std;

int t, n, q, w, x, y, z, L[100100], R[100100], wg[100100], distc[100100];
vector < int > cyc[100100], distL[100100], distR[100100];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &q);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &x);
            for (int j = 0; j < x; j++) {
                scanf("%d", &y);
                cyc[i].push_back(y);
            }
        }

        for (int i = 1; i <= n; i++) {
            scanf("%d %d %d", &x, &y, &z);
            R[i] = x;
            L[i % n + 1] = y;
            wg[i] = z;
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < cyc[i].size(); j++) {
                distL[i].push_back(INT_MAX);
                distR[i].push_back(INT_MAX);
            }

            int pos = L[i] - 1, d = 0;
            for (int j = 0; j < cyc[i].size(); j++) {
                distL[i][pos] = d;
                d += cyc[i][pos];
                pos++;
                if (pos == cyc[i].size()) pos -= cyc[i].size();
            }

            pos = L[i] - 1, d = 0;
            for (int j = 0; j < cyc[i].size(); j++) {
                distL[i][pos] = min(distL[i][pos], d);
                pos--;
                if (pos == -1) pos += cyc[i].size();
                d += cyc[i][pos];
            }

            pos = R[i] - 1, d = 0;
            for (int j = 0; j < cyc[i].size(); j++) {
                distR[i][pos] = d;
                d += cyc[i][pos];
                pos++;
                if (pos == cyc[i].size()) pos -= cyc[i].size();
            }

            pos = R[i] - 1, d = 0;
            for (int j = 0; j < cyc[i].size(); j++) {
                distR[i][pos] = min(distR[i][pos], d);
                pos--;
                if (pos == -1) pos += cyc[i].size();
                d += cyc[i][pos];
            }

            distc[i] = distL[i][R[i]-1];
        }

        for (int i = 2; i <= n; i++) {
            distc[i] += distc[i-1];
            wg[i] += wg[i-1];
        }

        for (int i = 0; i < q; i++) {
            scanf("%d %d %d %d", &w, &x, &y, &z);
            int a = 0, b = 0;
            a += distR[x][w-1];
            a += distL[z][y-1];
            b += distL[x][w-1];
            b += distR[z][y-1];
            if (x > z) {
                b += wg[n];
                a += wg[n] - wg[x-1];
                b -= wg[n] - wg[x-1];
                a += wg[z-1];
                b -= wg[z-1];

                b += distc[n] - distL[x][R[x]-1] - distL[z][R[z]-1];
                a += distc[z-1];
                b -= distc[z-1];
                a += distc[n] - distc[x];
                b -= distc[n] - distc[x];
            }
            else {
                b += wg[n];
                a += wg[z-1];
                b -= wg[z-1];
                a -= wg[x-1];
                b += wg[x-1];

                b += distc[n] - distL[x][R[x]-1] - distL[z][R[z]-1];
                a += distc[z-1] - distc[x];
                b -= distc[z-1] - distc[x];
            }

            printf("%d\n", min(a, b));
        }

        for (int i = 1; i <= n; i++) {
            L[i] = R[i] = wg[i] = distc[i] = 0;
            cyc[i].clear();
            distL[i].clear();
            distR[i].clear();
        }
    }

    return 0;
}

/*
5
2 3
3 4 4 4
5 1 2 3 4 5
2 3 1
5 2 1
1 2 2 1
*/
