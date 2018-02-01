#include <bits/stdc++.h>

using namespace std;

#define N 35500

int lastPos[N];

struct Node {
    int acum;
    Node *left, *right;

    Node(int acum, Node *left, Node *right) : acum(acum), left(left), right(right) {}

    Node* update(int ini, int fim, int pos, int val);
};

Node *null = new Node(0, NULL, NULL);

Node* Node::update(int ini, int fim, int pos, int val) {
    if (ini > pos || fim < pos) return this;

    if (ini == fim)
        return new Node(this->acum + val, null, null);

    int meio = (ini + fim) >> 1;

    return new Node(this->acum + val, this->left->update(ini, meio, pos, val), this->right->update(meio+1, fim, pos, val));
}

int persQuery(int ini, int fim, int start, int end, Node *atual) {
    if (start > fim || end < ini)
        return 0;
    if (ini >= start && fim <= end)
        return atual->acum;

    int meio = (ini + fim) >> 1;

    return persQuery(ini, meio, start, end, atual->left) + persQuery(meio+1, fim, start, end, atual->right);
}

Node *root[N];
int n, k, nums[N], dp[N][55], dif[N][1505];
bitset < N > aux;

void solve(int ini, int fim, int mini, int maxi, int lvl) {
    if (ini > fim) return;

    int mid = (ini + fim) >> 1;

    int ind = mini, x;
    for (int i = mini; i < min(maxi+1, mid); i++) {
        if (mid - i < 1500) x = dif[i+1][mid - i];
        else x = persQuery(1, n, i+2, mid+1, root[mid+1]);

        if (dp[mid][lvl] < dp[i][lvl-1] + x) {
            ind = i;
            dp[mid][lvl] = dp[i][lvl-1] + x;
        }
    }

    solve(ini, mid-1, mini, ind, lvl);
    solve(mid+1, fim, ind, maxi, lvl);
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);

    for (int i = 0; i < N; i++)
        lastPos[i] = -1;

    for (int i = 0; i < N; i++)
        root[i] = null;
    root[0]->left = root[0]->right = null;

    for (int i = 0; i < n; i++) {
        root[i+1] = root[i]->update(1, n, i+1, 1);
        if (lastPos[nums[i]] != -1)
            root[i+1] = root[i+1]->update(1, n, lastPos[nums[i]], -1);
        lastPos[nums[i]] = i+1;
    }

    memset(dp, -1, sizeof dp);

    for (int i = 0; i < n; i++) {
        int c = 0, cnt = 0;
        aux.reset();
        for (int j = i; j < n; j++) {
            c++;
            if (!aux.test(nums[j])) cnt++;
            dif[i][c] = cnt;
            aux.set(nums[j]);
            if (c == 1500) break;
        }
    }

    for (int i = 0; i < n; i++)
        dp[i][1] = persQuery(1, n, 1, i+1, root[i+1]);

    for (int i = 2; i <= k; i++)
        solve(0, n-1, 0, n-1, i);

    printf("%d\n", dp[n-1][k]);

    return 0;
}
