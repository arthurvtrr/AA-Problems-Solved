#include <bits/stdc++.h>

using namespace std;

int n, q, nums[3030], a, b;
char c;
int ans[3030][3030][2];
set < int > aux;
int pos[200200];

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
        aux.insert(nums[i]);
    }

    int cnt = 0;
    for (int v : aux)
        pos[v] = cnt++;

    memset(ans, -1, sizeof ans);

    for (int i = 0; i < n; i++) {
        int dist = 0;
        while (dist < n) {
            if (ans[i][pos[nums[(i-dist+n)%n]]][0] == -1) ans[i][pos[nums[(i-dist+n)%n]]][0] = dist;
            if (ans[i][pos[nums[(i+dist)%n]]][1] == -1) ans[i][pos[nums[(i+dist)%n]]][1] = dist;
            dist++;
        }
    }

    for (int i = 0; i < q; i++) {
        scanf("%d %d %c", &a, &b, &c);
        if (!aux.count(b)) printf("-1\n");
        else printf("%d\n", ans[a][pos[b]][c == 'L'? 0 : 1]);
    }

    return 0;
}
