#include <bits/stdc++.h>

using namespace std;

int m, n, nums[100100], cic[100100], pos[100100];
vector < int > cycles[100100];
vector < long long > sum[100100];

int main() {
    scanf("%d %d", &m, &n);
    for (int i = 1; i <= m; i++)
        scanf("%d", &nums[i]);

    int c = 1, p;
    for (int i = 1; i <= m; i++)
        if (!cic[i]) {
            p = 0;
            cic[i] = c;
            cycles[c].push_back(nums[i]);
            sum[c].push_back(nums[i]);
            pos[i] = p++;

            while (cycles[c][p-1] != i) {
                cic[cycles[c][p-1]] = c;
                cycles[c].push_back(nums[cycles[c][p-1]]);
                sum[c].push_back(nums[cycles[c][p-1]]);
                sum[c][p] += sum[c][p-1];
                pos[cycles[c][p-1]] = p++;
            }
            c++;
        }

    for (int i = 1; i <= m; i++) {
        if (i > 1) printf(" ");
        long long ans = 0;
        int siz = cycles[cic[i]].size();

        ans += sum[cic[i]][siz-1] * (n / siz);
        int left = n % siz;

        if (left != 0) {
            if (pos[i] + left - 1 < siz)
                ans += sum[cic[i]][pos[i] + left - 1] - (pos[i] == 0? 0 : sum[cic[i]][pos[i] - 1]);
            else {
                ans += sum[cic[i]][siz-1] - (pos[i] == 0? 0 : sum[cic[i]][pos[i] - 1]);
                left -= siz - pos[i];
                ans += sum[cic[i]][left-1];
            }
        }
        printf("%lld", ans);
    }

    return 0;
}

