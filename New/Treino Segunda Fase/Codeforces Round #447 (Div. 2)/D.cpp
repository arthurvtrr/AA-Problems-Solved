#include <bits/stdc++.h>

using namespace std;

#define ll long long

int n, m, x, y, nums[1001000], distp[1001000], distf[2][1001000], p[1001000];
vector < int > graph[1001000], dist[1001000];
vector < ll > acum[1001000];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 2; i <= n; i++) {
        scanf("%d", &nums[i]);
        distf[graph[i / 2].size()][i / 2] = nums[i];
        graph[i / 2].push_back(i);
        p[i] = i / 2;
        distp[i] = nums[i];
    }

    for (int i = 1; i <= n; i++) {
        int d = 0, u = i;
        while (u != 0) {
            dist[u].push_back(d);
            d += distp[u];
            u = p[u];
        }
    }

    for (int i = 1; i <= n; i++) {
        sort(dist[i].begin(), dist[i].end());
        for (int j = 0; j < dist[i].size(); j++) {
            acum[i].push_back(dist[i][j]);
            if (j) acum[i][j] += acum[i][j-1];
        }
    }

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        ll ans = 0;
        int aux = x, lft = y;
        ll total = 0;

        int ini = 0, fim = (int)dist[aux].size()-1;
        while (ini <= fim) {
            int mid = (ini + fim) / 2;
            if (dist[aux][mid] < lft) ini = mid+1;
            else fim = mid-1;
        }
        ll quant = y;
        quant *= fim+1;
        ans += quant;
        ans -= acum[aux][fim];

        while (aux != 1 && distp[aux] < lft) {
            ans += y;
            total += distp[aux];
            ans -= total;

            if (graph[p[aux]].size() < 2) { lft -= distp[aux]; aux = p[aux]; continue; }
            int nxt = graph[p[aux]][0] == aux? 1 : 0;
            if (distp[aux] + distf[nxt][p[aux]] >= lft) { lft -= distp[aux]; aux = p[aux]; continue; }

            int ini = 0, fim = (int)dist[graph[p[aux]][nxt]].size()-1;
            while (ini <= fim) {
                int mid = (ini + fim) / 2;
                if (dist[graph[p[aux]][nxt]][mid] < lft - distp[aux] - distf[nxt][p[aux]]) ini = mid+1;
                else fim = mid-1;
            }
            ll quant = y;
            quant *= fim+1;
            ans += quant;
            ans -= acum[graph[p[aux]][nxt]][fim] + total*(fim+1) + distf[nxt][p[aux]]*(fim+1);

            lft -= distp[aux];
            aux = p[aux];
        }

        printf("%lld\n", ans);
    }

    return 0;
}
