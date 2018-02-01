#include <bits/stdc++.h>

using namespace std;

#define pii pair < int, int >

int t, n, nums[1 << 18], ans[1 << 18], pos[20][1 << 18];
vector < pii > groups[20];
pii mins[20];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < 1 << n; i++)
            scanf("%d", &nums[i]);

        for (int i = 0; i < 20; i++)
            groups[i].clear();

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < 1 << n; j += 1 << i) {
                int maior = max(nums[j], nums[j+1]), seg = min(nums[j], nums[j+1]);
                for (int k = j+2; k < j + (1 << i); k++) {
                    if (nums[k] > maior) {
                        seg = maior;
                        maior = nums[k];
                    }
                    else if (nums[k] > seg) {
                        seg = nums[k];
                    }
                }

                for (int k = j; k < j + (1 << i); k++)
                    pos[i][k] = groups[i].size();

                groups[i].push_back(pii(maior, seg));
            }
        }

        for (int i = 1; i < n; i++) {
            int mini = groups[i][0].second, seg = groups[i][1].second;
            if (mini > seg) swap(mini, seg);
            for (int j = 0; j < groups[i].size(); j++) {
                if (groups[i][j].second < mini) {
                    seg = mini;
                    mini = groups[i][j].second;
                }
                else if (groups[i][j].second < seg) {
                    seg = groups[i][j].second;
                }
            }
            mins[i] = pii(mini, seg);
        }

        for (int i = 0; i < 1 << n; i++) {
            if (nums[i] == 1 << n) {
                ans[nums[i]-1] = n;
                continue;
            }
            if (nums[i] == 1) {
                ans[nums[i]-1] = 0;
                continue;
            }

            for (int j = n-1; j >= 1; j--) {
                if (nums[i] == groups[j][pos[j][i]].first) {
                    ans[nums[i]-1] = j;
                    break;
                }
                if (mins[j].first != groups[j][pos[j][i]].second && nums[i] > mins[j].first) {
                    ans[nums[i]-1] = j;
                    break;
                }
                if (mins[j].first == groups[j][pos[j][i]].second && nums[i] > mins[j].second) {
                    ans[nums[i]-1] = j;
                    break;
                }
            }
        }

        for (int i = 0; i < 1 << n; i++) {
            if (i) printf(" ");
            printf("%d", ans[i]);
        }
        printf("\n");
    }

    return 0;
}
