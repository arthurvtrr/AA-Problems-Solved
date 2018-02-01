#include <bits/stdc++.h>

using namespace std;

#define N 50050

struct Node {
    int val[2], acum[2];

    void atualize(int x, int t) {
        val[t] += x;
        acum[t] += x;
    }

    void shift(Node& left, Node& right) {
        left.atualize(acum[0], 0); left.atualize(acum[1], 1);
        right.atualize(acum[0], 0); right.atualize(acum[1], 1);
        acum[0] = acum[1] = 0;
    }

    void _merge(Node& left, Node& right) {
        val[0] = max(left.val[0], right.val[0]);
        val[1] = max(left.val[1], right.val[1]);
    }
} seg[4*N];

void update(int id, int ini, int fim, int start, int end, int val, int t) {
    if (start > fim || end < ini)
        return;
    if (ini >= start && fim <= end) {
        seg[id].atualize(val, t);
        return;
    }

    int meio = (ini + fim) / 2;
    seg[id].shift(seg[2*id], seg[2*id+1]);

    update(2*id, ini, meio, start, end, val, t);
    update(2*id+1, meio+1, fim, start, end, val, t);

    seg[id]._merge(seg[2*id], seg[2*id+1]);
}

int query(int id, int ini, int fim, int start, int end) {
    if (start > fim || end < ini)
        return 0;
    if (ini >= start && fim <= end)
        return max(seg[id].val[0], seg[id].val[1]);

    int meio = (ini + fim) / 2;
    seg[id].shift(seg[2*id], seg[2*id+1]);

    return max(query(2*id, ini, meio, start, end), query(2*id+1, meio+1, fim, start, end));
}

int t, n, m, s[50050], d[50050];
char typ[50050];
vector < int > posEC[50050], posDM[50050];
int dp[50050];

int main() {
    scanf("%d", &t);
    while (t--) {
        for (int i = 0; i < 50050; i++) {
            posEC[i].clear(); posDM[i].clear();
        }

        scanf("%d %d", &m, &n);
        for (int i = 1; i <= n; i++)
            scanf(" %c", &typ[i]);
        for (int i = 1; i <= n; i++)
            scanf("%d", &s[i]);
        for (int i = 1; i <= n; i++)
            scanf("%d", &d[i]);

        for (int i = 1; i <= n; i++) {
            if (s[i] < d[i] && typ[i] != 'E' && typ[i] != 'C') {
                posDM[s[i]].push_back(i);
                posDM[d[i]].push_back(i);
            }
            else if (s[i] < d[i]) {
                posEC[s[i]].push_back(i);
                posEC[d[i]].push_back(i);
            }
        }

        memset(dp, 0, sizeof dp);
        memset(seg, 0, sizeof seg);

        for (int i = 1; i <= m; i++) {
            for (int v : posEC[i]) {
                if (d[v] == i)
                    update(1, 1, m, 1, s[v], 1, 0);
            }
            for (int v : posDM[i]) {
                if (d[v] == i)
                    update(1, 1, m, 1, s[v], 1, 1);
            }
            dp[i] = query(1, 1, m, 1, i);
            update(1, 1, m, i, i, dp[i], 0);
            update(1, 1, m, i, i, dp[i], 1);
        }

        //for (int i = 1; i <= m; i++)
        //    printf("%d ", dp[i]);
        //printf("\n");

        int aux = 1;
        for (int i = 1; i <= n; i++) {
            if (i > 1) printf(" ");

            while (aux <= m && dp[aux] < i) aux++;
            if (aux > m) printf("-1");
            else printf("%d", aux);
        }
        printf("\n");
    }
    return 0;
}

/*
1
10 2
E D
3 8
9 10
*/
