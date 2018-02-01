#include <bits/stdc++.h>

using namespace std;

#define pii pair < int, int >

int t, w, h, n;
vector < int > aux[20200], used;

struct cic {
    int x, y, r;
} cics[110];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d %d", &w, &h, &n);
        for (int i = 0; i < n; i++)
            scanf("%d %d %d", &cics[i].x, &cics[i].y, &cics[i].r);

        int ans = w*h;
        for (int i = 0; i < w; i++) {
            used.clear();
            for (int j = 0; j < n; j++) {
                int dif = cics[j].r*cics[j].r - (cics[j].x - i)*(cics[j].x - i);
                if (dif >= 0) {
                    dif = sqrt(dif) + 1e-5;
                    aux[max(0, cics[j].y - dif)].push_back(min(h-1, cics[j].y + dif));
                    used.push_back(max(0, cics[j].y - dif));
                }
            }

            if (used.empty()) continue;

            sort(used.begin(), used.end());

            vector < pii > inv;
            for (int k = 0; k < used.size(); k++) {
                for (int j = 0; j < aux[used[k]].size(); j++)
                    inv.push_back(pii(used[k], aux[used[k]][j]));
                aux[used[k]].clear();
            }

            int aux = 0, maxi;
            for (int j = 0; j < inv.size(); j++) {
                if (j >= aux) maxi = inv[j].second;

                while (aux < inv.size() && inv[aux].first <= maxi) {
                    maxi = max(inv[aux].second, maxi);
                    aux++;
                }
                ans -= maxi - inv[j].first + 1;
                j = max(j, aux-1);
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}
