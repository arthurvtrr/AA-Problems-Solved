#include <bits/stdc++.h>

using namespace std;

int n, tmax;

struct prob {
    int t, p, id;
} ps[110];

bool cmp(prob a, prob b) {
    return a.p * b.t > b.p * a.t;
}

#define pii pair < int, int >

pii dp[110][1010];
int nxt[110][1010];

pii solve(int ind, int lft) {
    if (dp[ind][lft].first != -1) return dp[ind][lft];
    if (ind == n) return pii(0, 0);

    pii ret = solve(ind+1, lft);
    if (ps[ind].t <= lft) {
        pii aux = solve(ind+1, lft-ps[ind].t);
        aux.first += ps[ind].p;
        aux.second += ps[ind].p * (tmax - (lft-ps[ind].t));

        if (aux.first > ret.first) {
            ret = aux;
            nxt[ind][lft] = 1;
        }
        else if (aux.first == ret.first && aux.second < ret.second) {
            ret = aux;
            nxt[ind][lft] = 1;
        }
    }

    return dp[ind][lft] = ret;
}

int main() {
    scanf("%d %d", &n, &tmax);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &ps[i].t, &ps[i].p);
        ps[i].id = i+1;
    }

    for (int i = 0; i < 110; i++)
        for (int j = 0; j < 1010; j++)
            dp[i][j] = pii(-1, -1);

    sort(ps, ps+n, cmp);
    solve(0, tmax);

    vector < int > ans;
    int lft = tmax;
    for (int i = 0; i < n; i++) {
        if (nxt[i][lft] == 1) {
            ans.push_back(ps[i].id);
            lft -= ps[i].t;
        }
    }
    printf("%d\n", ans.size());
    for (int i = 0; i < ans.size(); i++) {
        if (i) printf(" ");
        printf("%d", ans[i]);
    }
    printf("\n");

    return 0;
}
