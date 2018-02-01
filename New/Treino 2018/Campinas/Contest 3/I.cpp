#include <bits/stdc++.h>

using namespace std;

int x, y, n, a, b;

struct plot {
   int p1[2], p2[2], id;
} ps[1010];

bool cmpx(plot a, plot b) {
    return a.p1[0] < b.p1[0];
}

bool cmpy(plot a, plot b) {
    return a.p1[1] < b.p1[1];
}

int dp[1010][10010], nxt[1010][10010], fim;

int solve(int ind, int lst, int t) {
    if (dp[ind][lst] != -1) return dp[ind][lst];
    if (ind == n) return lst == fim;

    int ret = solve(ind+1, lst, t);
    if (ps[ind].p1[t] == lst) {
        int aux = solve(ind+1, ps[ind].p2[t], t);
        if (aux) {
            ret = aux;
            nxt[ind][lst] = 1;
        }
    }
    return dp[ind][lst] = ret;
}

int main() {
    scanf("%d %d", &x, &y);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &ps[i].p1[0], &ps[i].p1[1], &ps[i].p2[0], &ps[i].p2[1]);
        ps[i].id = i+1;
    }
    scanf("%d %d", &a, &b);

    a--; b--;
    ps[n] = ps[a]; a = n;
    ps[n+1] = ps[b]; b = n+1;

    bool v = false;

    if (ps[a].p1[0] >= ps[b].p2[0] || ps[b].p1[0] >= ps[a].p2[0]) {
        sort(ps, ps+n, cmpx);
        bool p = true;
        vector < int > nw;

        memset(dp, -1, sizeof dp);
        memset(nxt, 0, sizeof nxt);

        fim = min(ps[a].p1[0], ps[b].p1[0]);
        int ret = solve(0, 0, 0);

        if (!ret) p = false;
        else {
            int aux = 0;
            for (int i = 0; i < n; i++) {
                if (nxt[i][aux]) {
                    nw.push_back(ps[i].id);
                    aux = ps[i].p2[0];
                }
            }
        }

        if (ps[a].p1[0] < ps[b].p1[0]) nw.push_back(ps[a].id);
        else nw.push_back(ps[b].id);

        memset(dp, -1, sizeof dp);
        memset(nxt, 0, sizeof nxt);

        fim = max(ps[a].p1[0], ps[b].p1[0]);
        ret = solve(0, min(ps[a].p2[0], ps[b].p2[0]), 0);

        if (!ret) p = false;
        else {
            int aux = min(ps[a].p2[0], ps[b].p2[0]);
            for (int i = 0; i < n; i++) {
                if (nxt[i][aux]) {
                    nw.push_back(ps[i].id);
                    aux = ps[i].p2[0];
                }
            }
        }

        if (ps[a].p1[0] > ps[b].p1[0]) nw.push_back(ps[a].id);
        else nw.push_back(ps[b].id);

        memset(dp, -1, sizeof dp);
        memset(nxt, 0, sizeof nxt);

        fim = x;
        ret = solve(0, max(ps[a].p2[0], ps[b].p2[0]), 0);

        if (!ret) p = false;
        else {
            int aux = max(ps[a].p2[0], ps[b].p2[0]);
            for (int i = 0; i < n; i++) {
                if (nxt[i][aux]) {
                    nw.push_back(ps[i].id);
                    aux = ps[i].p2[0];
                }
            }
        }

        if (p) {
            printf("%d\n", nw.size());
            for (int i = 0; i < nw.size(); i++) {
                if (i) printf(" ");
                printf("%d", nw[i]);
            }
            printf("\n");
            return 0;
        }
    }

    if (ps[a].p1[1] >= ps[b].p2[1] || ps[b].p1[1] >= ps[a].p2[1]) {
        sort(ps, ps+n, cmpy);
        bool p = true;
        vector < int > nw;

        memset(dp, -1, sizeof dp);
        memset(nxt, 0, sizeof nxt);

        fim = min(ps[a].p1[1], ps[b].p1[1]);
        int ret = solve(0, 0, 1);

        if (!ret) p = false;
        else {
            int aux = 0;
            for (int i = 0; i < n; i++) {
                if (nxt[i][aux]) {
                    nw.push_back(ps[i].id);
                    aux = ps[i].p2[1];
                }
            }
        }

        if (ps[a].p1[1] < ps[b].p1[1]) nw.push_back(ps[a].id);
        else nw.push_back(ps[b].id);

        memset(dp, -1, sizeof dp);
        memset(nxt, 0, sizeof nxt);

        fim = max(ps[a].p1[1], ps[b].p1[1]);
        ret = solve(0, min(ps[a].p2[1], ps[b].p2[1]), 1);

        if (!ret) p = false;
        else {
            int aux = min(ps[a].p2[1], ps[b].p2[1]);
            for (int i = 0; i < n; i++) {
                if (nxt[i][aux]) {
                    nw.push_back(ps[i].id);
                    aux = ps[i].p2[1];
                }
            }
        }

        if (ps[a].p1[1] > ps[b].p1[1]) nw.push_back(ps[a].id);
        else nw.push_back(ps[b].id);

        memset(dp, -1, sizeof dp);
        memset(nxt, 0, sizeof nxt);

        fim = y;
        ret = solve(0, max(ps[a].p2[1], ps[b].p2[1]), 1);

        if (!ret) p = false;
        else {
            int aux = max(ps[a].p2[1], ps[b].p2[1]);
            for (int i = 0; i < n; i++) {
                if (nxt[i][aux]) {
                    nw.push_back(ps[i].id);
                    aux = ps[i].p2[1];
                }
            }
        }

        if (p) {
            printf("%d\n", nw.size());
            for (int i = 0; i < nw.size(); i++) {
                if (i) printf(" ");
                printf("%d", nw[i]);
            }
            printf("\n");
            return 0;
        }
    }

    printf("-1\n");
    return 0;
}

/*
4 4
7
2 0 4 1
3 1 4 3
1 1 3 3
1 3 4 4
1 0 2 1
0 0 1 2
0 2 1 4
2 5
*/
