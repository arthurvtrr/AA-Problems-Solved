#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define INF 10000000000000000LL

int t, n, b, c, nums[3030], typ;
ll dp[3][3030][3030], fjump[3][3030][3030], nrm[3030][3030], inv[3030][3030], best[3030][3030];
vector < int > atual;

void solve(int ini, int fim, int mini, int maxi, int lvl) {
    if (ini > fim) return;

    int mid = (ini + fim) / 2;

    int ind = mini;
    for (int i = mini; i < min(maxi+1, mid); i++) {
        ll x = nums[atual[mid]] - nums[atual[i]];
        if (dp[typ][mid][lvl] > dp[typ][i][lvl-1] + x*x) {
            ind = i;
            dp[typ][mid][lvl] = dp[typ][i][lvl-1] + x*x;

            if (atual[i] == c) fjump[typ][mid][lvl] = atual[mid];
            else fjump[typ][mid][lvl] = fjump[typ][i][lvl-1];
        }
    }

    solve(ini, mid-1, mini, ind, lvl);
    solve(mid+1, fim, ind, maxi, lvl);
}

ll cnrm(int ini, int lvl) {
    if (lvl < 0) return INF;
    if (nrm[ini][lvl] != -1) return nrm[ini][lvl];

    atual.clear();
    for (int i = n-1; i >= 0; i--)
        atual.push_back(i);
    int siz = atual.size();

    typ = 2;
    for (int i = 0; i < siz; i++)
        for (int j = 0; j <= b; j++)
            dp[2][i][j] = INF;

    for (int i = 0; i <= b; i++)
        dp[2][0][i] = 0;

    for (int i = 1; i <= b; i++)
        solve(0, siz-1, 0, siz-1, i);

    for (int i = 0; i < n; i++)
        for (int j = 0; j <= b; j++)
            nrm[n-1-i][j] = dp[2][i][j];

    return nrm[ini][lvl];
}

ll cinv(int ini, int lvl) {
    if (lvl < 0) return INF;
    if (inv[ini][lvl] != -1) return inv[ini][lvl];

    atual.clear();
    for (int i = 0; i < n; i++)
        atual.push_back(i);
    int siz = atual.size();

    typ = 2;
    for (int i = 0; i < siz; i++)
        for (int j = 0; j <= b; j++)
            dp[2][i][j] = INF;

    for (int i = 0; i <= b; i++)
        dp[2][0][i] = 0;

    for (int i = 1; i <= b; i++)
        solve(0, siz-1, 0, siz-1, i);

    for (int i = 0; i < n; i++)
        for (int j = 0; j <= b; j++)
            inv[i][j] = dp[2][i][j];

    return inv[ini][lvl];
}

ll val(int nxt, int c, int lft, ll mini) {
    nxt = min(nxt, n-1);
    if (mini == -1) mini = best[c][nxt];

    if (nxt > c) {
        ll aux = nums[nxt] - nums[c];
        aux *= aux;
        aux += cnrm(nxt, lft-1);
        if (c != 0) {
            if (min(mini, best[c][nxt]) == c) return INF;
            aux += cinv(min(mini, best[c][nxt]), lft-1);
        }
        return aux;
    }

    ll aux = nums[c] - nums[nxt];
    aux *= aux;
    if (c != n-1) {
        if (max(mini, best[c][nxt]) == c) return INF;
        aux += cnrm(max(mini, best[c][nxt]), lft-1);
    }
    aux += cinv(nxt, lft-1);
    return aux;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d %d", &n, &b, &c);
        c--;

        memset(nums, 0, sizeof nums);
        memset(best, 0, sizeof best);
        for (int i = 0; i < 3030; i++)
            for (int j = 0; j < 3030; j++)
                dp[0][i][j] = dp[1][i][j] = dp[2][i][j] = INF;
        memset(fjump, -1, sizeof fjump);
        memset(nrm, -1, sizeof nrm);
        memset(inv, -1, sizeof inv);

        for (int i = 0; i < n; i++)
            scanf("%d", &nums[i]);

        if (n == 1) {
            printf("0\n");
            continue;
        }
        if (b == 1) {
            ll a = nums[c] - nums[0], b = nums[n-1] - nums[c];
            printf("%lld\n", max(a*a, b*b));
            continue;
        }

        for (int i = 0; i < n; i++) {
            int nxt = i;
            for (int j = i; j < n; j++) {
                while (nxt && nums[i] - nums[nxt-1] <= nums[j] - nums[i]) nxt--;
                best[i][j] = nxt;
            }

            nxt = i;
            for (int j = i-1; j >= 0; j--) {
                while (nxt < n-1 && nums[nxt+1] - nums[i] <= nums[i] - nums[j]) nxt++;
                best[i][j] = nxt;
            }
        }

        atual.clear();
        for (int i = c; i >= 0; i--)
            atual.push_back(i);
        int siz = atual.size();

        for (int i = 0; i < siz; i++)
            for (int j = 0; j <= b; j++)
                dp[0][i][j] = INF;

        for (int i = 0; i <= b; i++)
            dp[0][0][i] = 0;

        typ = 0;
        for (int i = 1; i <= b; i++)
            solve(0, siz-1, 0, siz-1, i);

        atual.clear();
        for (int i = c; i < n; i++)
            atual.push_back(i);
        siz = atual.size();

        for (int i = 0; i < siz; i++)
            for (int j = 0; j <= b; j++)
                dp[1][i][j] = INF;

        for (int i = 0; i <= b; i++)
            dp[1][0][i] = 0;

        typ = 1;
        for (int i = 1; i <= b; i++)
            solve(0, siz-1, 0, siz-1, i);

        ll ans = LLONG_MAX;
        for (int nxt = 0; nxt <= c; nxt++) {
            for (int i = 0; i <= b; i++) {
                ll aux = dp[0][c-nxt][i], f = fjump[0][c-nxt][i], bt = (f == -1? -1 : best[c][f]);

                if (n - nxt < 2000)
                    for (int j = nxt+1; j < n; j++)
                        ans = min(ans, aux + val(j, nxt, b-i, bt));

                int ini = nxt, fim = n-1;
                while (fim - ini > 1) {
                    int mid = (ini + fim) / 2;
                    if (val(mid, nxt, b-i, bt) < val(mid+1, nxt, b-i, bt)) fim = mid;
                    else ini = mid;
                }
                ans = min(ans, aux + val(ini+1, nxt, b-i, bt));

                if (nxt < 2000)
                    for (int j = 0; j <= nxt; j++)
                        ans = min(ans, aux + val(j, nxt, b-i, bt));

                ini = -1, fim = nxt-1;
                while (fim - ini > 1) {
                    int mid = (ini + fim) / 2;
                    if (val(mid, nxt, b-i, bt) < val(mid+1, nxt, b-i, bt)) fim = mid;
                    else ini = mid;
                }
                ans = min(ans, aux + val(ini+1, nxt, b-i, bt));
            }
        }

        for (int nxt = c+1; nxt < n; nxt++) {
            for (int i = 0; i <= b; i++) {
                ll aux = dp[1][nxt-c][i], f = fjump[1][nxt-c][i], bt = (f == -1? -1 : best[c][f]);

                if (n - nxt < 2000)
                    for (int j = nxt+1; j < n; j++)
                        ans = min(ans, aux + val(j, nxt, b-i, bt));

                int ini = nxt, fim = n-1;
                while (fim - ini > 1) {
                    int mid = (ini + fim) / 2;
                    if (val(mid, nxt, b-i, bt) < val(mid+1, nxt, b-i, bt)) fim = mid;
                    else ini = mid;
                }
                ans = min(ans, aux + val(ini+1, nxt, b-i, bt));

                if (nxt < 2000)
                    for (int j = 0; j <= nxt; j++)
                        ans = min(ans, aux + val(j, nxt, b-i, bt));

                ini = -1, fim = nxt-1;
                while (fim - ini > 1) {
                    int mid = (ini + fim) / 2;
                    if (val(mid, nxt, b-i, bt) < val(mid+1, nxt, b-i, bt)) fim = mid;
                    else ini = mid;
                }
                ans = min(ans, aux + val(ini+1, nxt, b-i, bt));
            }
        }

        printf("%lld\n", ans);
    }

    return 0;
}
