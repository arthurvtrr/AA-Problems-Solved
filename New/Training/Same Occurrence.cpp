#include <bits/stdc++.h>

using namespace std;

#define N 8080
#define pii pair < int, int >

int n, q, nums[N], x, y, ans[N][N], tot[N], sum[N];
vector < int > pos[N];
set < int > aux;
map < int, int > ind;

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
        aux.insert(nums[i]);
    }

    int cnt = 1;
    for (int v : aux)
        ind[v] = cnt++;

    for (int i = 0; i < n; i++)
        pos[ind[nums[i]]].push_back(i);

    for (int i = 0; i < N; i++)
        if (!pos[i].empty()) {
            int lst = -1, val = 0;
            for (int v : pos[i]) {
                val += (v - lst) * (v - lst - 1) / 2;
                lst = v;
            }
            tot[i] = val + (n - lst) * (n - lst - 1) / 2;
        }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            ans[i][j] = -1;

    for (int i = 0; i < q; i++) {
        scanf("%d %d", &x, &y);
        if (x > y) swap(x, y);

        if ((!aux.count(x) && !aux.count(y)) || x == y) printf("%d\n", n * (n+1) / 2);
        else if (!aux.count(y)) printf("%d\n", tot[ind[x]]);
        else if (!aux.count(x)) printf("%d\n", tot[ind[y]]);
        else {
            x = ind[x], y = ind[y];
            if (ans[x][y] != -1) printf("%d\n", ans[x][y]);
            else {
                for (int v : pos[x]) sum[v] = 0;
                for (int v : pos[y]) sum[v] = 0;

                vector < pii > bet;

                int a = 0, b = 0;
                while (a < pos[x].size() && b < pos[y].size()) {
                    if (pos[x][a] < pos[y][b]) {
                        bet.push_back(pii(pos[x][a], 0));
                        a++;
                    }
                    else {
                        bet.push_back(pii(pos[y][b], 1));
                        b++;
                    }
                }
                while (a < pos[x].size()) {
                    bet.push_back(pii(pos[x][a], 0));
                    a++;
                }
                while (b < pos[y].size()) {
                    bet.push_back(pii(pos[y][b], 1));
                    b++;
                }

                stack < int > atualx, atualy;
                for (int i = 0; i < bet.size(); i++) {
                    if (bet[i].second == 0) {
                        if (!atualy.empty() && bet[atualy.top()].second != bet[i].second) {
                            int v = atualy.top();
                            sum[bet[i].first] = bet[v].first - (v == 0? -1 : bet[v-1].first) + (v == 0? 0 : sum[bet[v-1].first]);
                            atualy.pop();
                        }
                        atualx.push(i);
                    }
                    else {
                        if (!atualx.empty() && bet[atualx.top()].second != bet[i].second) {
                            int v = atualx.top();
                            sum[bet[i].first] = bet[v].first - (v == 0? -1 : bet[v-1].first) + (v == 0? 0 : sum[bet[v-1].first]);
                            atualx.pop();
                        }
                        atualy.push(i);
                    }
                }

                ans[x][y] = 0;
                for (int i = 0; i < bet.size(); i++)
                    ans[x][y] += sum[bet[i].first] * (i == (bet.size() - 1)? n - bet[i].first : bet[i+1].first - bet[i].first);
                for (int i = 0; i < bet.size(); i++)
                    ans[x][y] += (i == 0? bet[i].first * (bet[i].first + 1) / 2 : (bet[i].first - bet[i-1].first) * (bet[i].first - bet[i-1].first - 1) / 2);
                ans[x][y] += (n - bet.back().first) * (n - bet.back().first - 1) / 2;

                printf("%d\n", ans[x][y]);
            }
        }
    }

    return 0;
}
