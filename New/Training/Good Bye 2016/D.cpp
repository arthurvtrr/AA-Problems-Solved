#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

int n, nums[50];
bool visited[320][320], used[320][320][31][3][3];

void dfs(int x, int y, int dep, int cx, int cy) {
    used[x][y][dep][cx+1][cy+1] = true;

    if (dep > n) return;

    if (cx == 0 && cy == 0) {
        int auxx = x, auxy = y;

        for (int i = 0; i < nums[dep]; i++) {
            auxy++;
            visited[auxx][auxy] = true;
        }

        if (!used[auxx][auxy][dep+1][1][2])
            dfs(auxx, auxy, dep+1, 0, 1);
    }

    if (cx == 0 && cy == 1) {
        int auxx = x, auxy = y;

        for (int i = 0; i < nums[dep]; i++) {
            auxx++; auxy++;
            visited[auxx][auxy] = true;
        }
        if (!used[auxx][auxy][dep+1][2][2])
            dfs(auxx, auxy, dep+1, 1, 1);

        auxx = x, auxy = y;

        for (int i = 0; i < nums[dep]; i++) {
            auxx--; auxy++;
            visited[auxx][auxy] = true;
        }
        if (!used[auxx][auxy][dep+1][0][2])
            dfs(auxx, auxy, dep+1, -1, 1);
    }

    if (cx == 1 && cy == 1) {
        int auxx = x, auxy = y;

        for (int i = 0; i < nums[dep]; i++) {
            auxy++;
            visited[auxx][auxy] = true;
        }
        if (!used[auxx][auxy][dep+1][1][2])
            dfs(auxx, auxy, dep+1, 0, 1);

        auxx = x, auxy = y;

        for (int i = 0; i < nums[dep]; i++) {
            auxx++;
            visited[auxx][auxy] = true;
        }
        if (!used[auxx][auxy][dep+1][2][1])
            dfs(auxx, auxy, dep+1, 1, 0);
    }

    if (cx == 1 && cy == 0) {
        int auxx = x, auxy = y;

        for (int i = 0; i < nums[dep]; i++) {
            auxx++; auxy++;
            visited[auxx][auxy] = true;
        }
        if (!used[auxx][auxy][dep+1][2][2])
            dfs(auxx, auxy, dep+1, 1, 1);

        auxx = x, auxy = y;

        for (int i = 0; i < nums[dep]; i++) {
            auxx++; auxy--;
            visited[auxx][auxy] = true;
        }
        if (!used[auxx][auxy][dep+1][2][0])
            dfs(auxx, auxy, dep+1, 1, -1);
    }

    if (cx == 1 && cy == -1) {
        int auxx = x, auxy = y;

        for (int i = 0; i < nums[dep]; i++) {
            auxx++;
            visited[auxx][auxy] = true;
        }
        if (!used[auxx][auxy][dep+1][2][1])
            dfs(auxx, auxy, dep+1, 1, 0);

        auxx = x, auxy = y;

        for (int i = 0; i < nums[dep]; i++) {
            auxy--;
            visited[auxx][auxy] = true;
        }
        if (!used[auxx][auxy][dep+1][1][0])
            dfs(auxx, auxy, dep+1, 0, -1);
    }
    if (cx == 0 && cy == -1) {
        int auxx = x, auxy = y;

        for (int i = 0; i < nums[dep]; i++) {
            auxx++; auxy--;
            visited[auxx][auxy] = true;
        }
        if (!used[auxx][auxy][dep+1][2][0])
            dfs(auxx, auxy, dep+1, 1, -1);

        auxx = x, auxy = y;

        for (int i = 0; i < nums[dep]; i++) {
            auxy--; auxx--;
            visited[auxx][auxy] = true;
        }
        if (!used[auxx][auxy][dep+1][0][0])
            dfs(auxx, auxy, dep+1, -1, -1);
    }
    if (cx == -1 && cy == -1) {
        int auxx = x, auxy = y;

        for (int i = 0; i < nums[dep]; i++) {
            auxy--;
            visited[auxx][auxy] = true;
        }
        if (!used[auxx][auxy][dep+1][1][0])
            dfs(auxx, auxy, dep+1, 0, -1);

        auxx = x, auxy = y;

        for (int i = 0; i < nums[dep]; i++) {
            auxx--;
            visited[auxx][auxy] = true;
        }
        if (!used[auxx][auxy][dep+1][0][1])
            dfs(auxx, auxy, dep+1, -1, 0);
    }
    if (cx == -1 && cy == 0) {
        int auxx = x, auxy = y;

        for (int i = 0; i < nums[dep]; i++) {
            auxx--; auxy--;
            visited[auxx][auxy] = true;
        }
        if (!used[auxx][auxy][dep+1][0][0])
            dfs(auxx, auxy, dep+1, -1, -1);

        auxx = x, auxy = y;

        for (int i = 0; i < nums[dep]; i++) {
            auxx--; auxy++;
            visited[auxx][auxy] = true;
        }
        if (!used[auxx][auxy][dep+1][0][2])
            dfs(auxx, auxy, dep+1, -1, 1);
    }
    if (cx == -1 && cy == 1) {
        int auxx = x, auxy = y;

        for (int i = 0; i < nums[dep]; i++) {
            auxx--;
            visited[auxx][auxy] = true;
        }
        if (!used[auxx][auxy][dep+1][0][1])
            dfs(auxx, auxy, dep+1, -1, 0);

        auxx = x, auxy = y;

        for (int i = 0; i < nums[dep]; i++) {
            auxy++;
            visited[auxx][auxy] = true;
        }
        if (!used[auxx][auxy][dep+1][1][2])
            dfs(auxx, auxy, dep+1, 0, 1);
    }
}

int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &nums[i]);
    }

    dfs(160, 160, 1, 0, 0);

    int sol = 0;
    for (int i = 0; i < 320; i++)
        for (int j = 0; j < 320; j++)
            if (visited[i][j]) sol++;

    printf("%d\n", sol);

    return 0;
}

