#include <bits/stdc++.h>

using namespace std;

#define pii pair < int, int >

int n, k, a, b, maxi[22][1001000];
vector < pii > ways;

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < k; i++) {
        scanf("%d %d", &a, &b);
        if (a > b) {
            maxi[0][a] = max(maxi[0][a], n);
            ways.push_back(pii(a, b));
        }
        else maxi[0][a] = max(maxi[0][a], b);
    }

    for (int i = 1; i < 1001000; i++)
        maxi[0][i] = max(maxi[0][i], maxi[0][i-1]);

    for (int i = 1; i < 22; i++) {
        for (int j = 0; j < 1001000; j++)
            maxi[i][j] = maxi[i-1][maxi[i-1][j]+1];
    }

    int ans = INT_MAX;
    ways.push_back(pii(n+1, 0));
    for (int i = 0; i < ways.size(); i++) {
        int aux = (ways[i].first != n+1), x = ways[i].second, fim = ways[i].first - 1;

        while (x < fim) {
            int s = 0, t = 21;
            while (s <= t) {
                int meio = (s + t) / 2;
                if (maxi[meio][x+1] >= n) t = meio-1;
                else s = meio+1;
            }

            if (s > 21) { aux = INT_MAX; break; }
            x = maxi[max(0, t)][x+1];
            aux += 1 << (max(0, t));
        }
        ans = min(ans, aux);
    }

    if (ans == INT_MAX) printf("impossible\n");
    else printf("%d\n", ans);

    return 0;
}

