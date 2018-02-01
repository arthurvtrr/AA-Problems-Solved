#include <bits/stdc++.h>

using namespace std;

int n, nums[100100], cop[100100];
bool app[100100];
vector < int > subs[100100];
map < int, int > ind;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &nums[i]);
        cop[i] = nums[i];
    }

    sort(cop+1, cop+n+1);

    int pos = 1;
    for (int i = 1; i <= n; i++)
        ind[cop[i]] = pos++;

    for (int i = 1; i <= n; i++)
        nums[i] = ind[nums[i]];

    int sub = 0;
    for (int i = 1; i <= n; i++) {
        if (app[i]) continue;

        subs[sub].push_back(nums[i]);
        app[i] = true;
        int aux = i;

        while (!app[nums[aux]]) {
            aux = nums[aux];
            subs[sub].push_back(nums[aux]);
            app[aux] = true;
        }

        sub++;
    }

    printf("%d\n", sub);
    for (int i = 0; i < sub; i++) {
        printf("%d", subs[i].size());
        for (int v : subs[i])
            printf(" %d", v);
        printf("\n");
    }

    return 0;
}
