#include <bits/stdc++.h>

using namespace std;

#define N 100100

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

    int meio = (ini + fim) / 2;

    return new Node(this->acum + val, this->left->update(ini, meio, pos, val), this->right->update(meio+1, fim, pos, val));
}

int persQuery(int ini, int fim, int start, int end, Node *atual) {
    if (start > fim || end < ini)
        return 0;
    if (ini >= start && fim <= end)
        return atual->acum;

    int meio = (ini + fim) / 2;

    return persQuery(ini, meio, start, end, atual->left) + persQuery(meio+1, fim, start, end, atual->right);
}

Node *root[N];

int n, k, nums[N], q, x, y, prv[N];
vector < int > pos[N];

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &nums[i]);
        pos[nums[i]].push_back(i);
    }

    for (int i = 0; i < N; i++)
        if (pos[i].size() > k)
            for (int j = k; j < pos[i].size(); j++)
                prv[pos[i][j]] = pos[i][j-k];

    for (int i = 0; i < N; i++)
        root[i] = null;
    root[0]->left = root[0]->right = null;

    for (int i = 1; i <= n; i++)
        root[i] = root[i-1]->update(0, n, prv[i], 1);

    scanf("%d", &q);
    int last = 0;
    for (int i = 0; i < q; i++) {
        scanf("%d %d", &x, &y);
        int l = ((x + last) % n) + 1, r = ((y + last) % n) + 1;
        if (l > r) swap(l, r);

        last = persQuery(0, n, 0, l-1, root[r]) - persQuery(0, n, 0, l-1, root[l-1]);
        printf("%d\n", last);
    }

    return 0;
}
