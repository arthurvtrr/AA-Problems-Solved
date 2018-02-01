#include <bits/stdc++.h>

using namespace std;

int n, k, d;
vector < vector < int > > groups, sub;
int ans[1010];

int main() {
    scanf("%d %d %d", &n, &k, &d);
    if (k >= n) {
        for (int i = 0; i < d; i++) {
            for (int j = 1; j <= n; j++) {
                if (j > 1) printf(" ");
                printf("%d", j);
            }
            printf("\n");
        }
    }
    else {
        int x = 1;
        for (int i = 0; i < d; i++) {
            x *= k;
            if (x >= n) break;
        }

        if (n > x) printf("-1\n");
        else {
            vector < int > ini;
            for (int i = 1; i <= n; i++)
                ini.push_back(i);
            groups.push_back(ini);

            for (int i = 0; i < d; i++) {
                for (int j = 0; j < groups.size(); j++) {
                    vector < int > nw;

                    int bus = 1, siz = groups[j].size(), div = (siz + k - 1) / k;
                    for (int a = 0; a < siz; a++) {
                        ans[groups[j][a]] = bus;
                        nw.push_back(groups[j][a]);
                        if ((a+1) % div == 0) {
                            sub.push_back(nw);
                            nw.clear();
                            bus++;
                        }
                    }

                    if (!nw.empty())
                        sub.push_back(nw);
                }

                groups.clear();
                for (int j = 0; j < sub.size(); j++)
                    groups.push_back(sub[j]);
                sub.clear();

                for (int j = 1; j <= n; j++) {
                    if (j > 1) printf(" ");
                    printf("%d", ans[j]);
                }
                printf("\n");
            }
        }
    }

    return 0;
}
