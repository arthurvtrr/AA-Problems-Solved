#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define N 1001000

ll seg[4*N];
vector < int > aux[2];
vector < ll > nums;

void build(int id, int ini, int fim) {
    if (ini == fim) {
        seg[id] = nums[ini-1];
        return;
    }
    int meio = (ini + fim) / 2;

    build(2*id, ini, meio);
    build(2*id+1, meio+1, fim);

    seg[id] = max(seg[2*id], seg[2*id+1]);
}

void update(int id, int ini, int fim, int pos, ll val) {
    if (ini == fim) {
        seg[id] = val;
        return;
    }
    int meio = (ini + fim) / 2;

    if (pos <= meio) update(2*id, ini, meio, pos, val);
    else update(2*id+1, meio+1, fim, pos, val);

    seg[id] = max(seg[2*id], seg[2*id+1]);
}

ll query(int id, int ini, int fim, int start, int end) {
    if (start > fim || end < ini)
        return LLONG_MIN;
    if (ini >= start && fim <= end)
        return seg[id];

    int meio = (ini + fim) / 2;

	return max(query(2*id, ini, meio, start, end), query(2*id+1, meio+1, fim, start, end));
}

int t, n, m, x, atual;
vector < ll > ing[N], dp[N];

bool cmp(int a, int b) {
    return ing[atual][a] < ing[atual][b];
}

int main() {
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &m);
            for (int j = 0; j < m; j++) {
                scanf("%d", &x);
                ing[i].push_back(x);
                dp[i].push_back(0);
            }
        }

        for (int i = 1; i < n; i++) {
            aux[0].clear(); aux[1].clear(); nums.clear();

            for (int j = 0; j < ing[i-1].size(); j++)
                aux[0].push_back(j);
            for (int j = 0; j < ing[i].size(); j++)
                aux[1].push_back(j);

            atual = i-1;
            sort(aux[0].begin(), aux[0].end(), cmp);
            atual = i;
            sort(aux[1].begin(), aux[1].end(), cmp);

            for (int j = 0; j < aux[0].size(); j++)
                nums.push_back(dp[i-1][(aux[0][j] + 1) % aux[0].size()] + ing[i-1][aux[0][j]] * i);
            build(1, 1, aux[0].size()+1);

            int x = 0;
            for (int j = 0; j < aux[1].size(); j++) {
                while (x < aux[0].size() && ing[i-1][aux[0][x]] < ing[i][aux[1][j]]) {
                    update(1, 1, aux[0].size()+1, x+1, dp[i-1][(aux[0][x] + 1) % aux[0].size()] - ing[i-1][aux[0][x]] * i);
                    x++;
                }

                if (x) dp[i][aux[1][j]] = max(dp[i][aux[1][j]], query(1, 1, aux[0].size()+1, 1, x) + ing[i][aux[1][j]] * i);
                if (x < aux[0].size()) dp[i][aux[1][j]] = max(dp[i][aux[1][j]], query(1, 1, aux[0].size()+1, x+1, aux[0].size()) - ing[i][aux[1][j]] * i);
            }
        }

        ll ans = 0;
        for (int i = 0; i < dp[n-1].size(); i++)
            ans = max(ans, dp[n-1][i]);
        printf("%lld\n", ans);

        for (int i = 0; i < n; i++) {
            ing[i].clear();
            dp[i].clear();
        }
    }

    return 0;
}
