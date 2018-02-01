#include <bits/stdc++.h>

using namespace std;

int h, nums[100100];

int main() {
    scanf("%d", &h);
    for (int i = 0; i < h+1; i++)
        scanf("%d", &nums[i]);

    bool found = false;
    for (int i = 0; i < h; i++)
        if (nums[i] > 1 && nums[i+1] > 1)
            found = true;

    if (!found) printf("perfect\n");
    else {
        vector < int > ans[2];
        int aux = 1;
        ans[0].push_back(0);
        for (int i = 1; i < h+1; i++) {
            for (int j = 0; j < nums[i]; j++)
                ans[0].push_back(aux);
            aux += nums[i-1];
        }

        aux = 1;
        ans[1].push_back(0);
        for (int i = 1; i < h+1; i++) {
            for (int j = 0; j < nums[i]; j++) {
                if (nums[i-1] > 1 && nums[i] > 1) ans[1].push_back(aux + (j&1));
                else ans[1].push_back(aux);
            }
            aux += nums[i-1];
        }

        printf("ambiguous\n");
        for (int i = 0; i < ans[0].size(); i++) {
            if (i) printf(" ");
            printf("%d", ans[0][i]);
        }
        printf("\n");
        for (int i = 0; i < ans[1].size(); i++) {
            if (i) printf(" ");
            printf("%d", ans[1][i]);
        }
        printf("\n");
    }

    return 0;
}
