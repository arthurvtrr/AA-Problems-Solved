#include <bits/stdc++.h>

using namespace std;

#define INF 1000000000

int n, x, ans[30][30];
string s;
vector < int > masks, pos[1 << 25];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        for (int j = 0; j < x; j++) {
            cin >> s;

            int mask = 0;
            for (char c : s)
                mask += 1 << (c - 'a');

            masks.push_back(mask);
            pos[mask].push_back(i);
        }
    }

    sort(masks.begin(), masks.end());
    vector<int>::iterator it = unique(masks.begin(), masks.end());
    masks.resize(distance(masks.begin(), it));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            ans[i][j] = INF;

    for (int q = 0; q < n; q++) {
        int temp = 1 << q;
        ans[q][q] = 0;

        for (int i = 0; i < n-1; i++) {
            int add = 0;

            for (int j = 0; j < masks.size(); j++)
                if ((masks[j] | temp) == temp) {
                    int aux = 0;
                    for (int k = 0; k < n; k++)
                        if (masks[j] & (1 << k))
                            aux = max(aux, ans[k][q]);

                    for (int v : pos[masks[j]])
                        if (!(temp & (1 << v))) {
                            ans[v][q] = min(ans[v][q], aux + 1);
                            add |= 1 << v;
                        }
                }

            if (!add) break;
            temp |= add;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j) printf(" ");
            printf("%d", ans[i][j] == INF? -1 : ans[i][j]);
        }
        printf("\n");
    }

    return 0;
}
