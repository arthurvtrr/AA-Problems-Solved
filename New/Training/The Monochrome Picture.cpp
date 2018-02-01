#include <bits/stdc++.h>

using namespace std;

#define N 100100
#define MAXM 1001000

int n, nums[N], last[N];

struct Node {
    int val;
    int pos;

    Node() { val = 0; pos = -1; }
    Node(int v, int p) { val = v; pos = p; }

} seg[4*MAXM];

void update(int id, int ini, int fim, int pos, int val, int ind) {
    if (ini == fim) {
        seg[id].val = val;
        seg[id].pos = ind;
        return;
    }
    int meio = (ini + fim) / 2;

    if (pos <= meio) update(2*id, ini, meio, pos, val, ind);
    else update(2*id+1, meio+1, fim, pos, val, ind);

    if (seg[2*id].val < seg[2*id+1].val) seg[id] = seg[2*id+1];
    else seg[id] = seg[2*id];
}

Node query(int id, int ini, int fim, int start, int end) {
    if (start > fim || end < ini)
        return Node(0, -1);
    if (ini >= start && fim <= end)
        return seg[id];

    int meio = (ini + fim) / 2;

    Node left = query(2*id, ini, meio, start, end);
    Node right = query(2*id+1, meio+1, fim, start, end);

    if (left.val < right.val) return right;
    return left;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
        nums[i] += 3;
    }

    for (int i = 0; i < n; i++) {
        Node a, b, c;
        a = query(1, 1, MAXM, 1, nums[i]-2);
        b = query(1, 1, MAXM, nums[i], nums[i]);
        c = query(1, 1, MAXM, nums[i]+2, MAXM);

        if (c.val > b.val) b = c;
        if (b.val > a.val) a = b;

        update(1, 1, MAXM, nums[i], a.val + 1, i);
        last[i] = a.pos;
    }

    vector < int > ans;

    int aux = seg[1].pos;
    while (aux != -1) {
        ans.push_back(nums[aux] - 3);
        aux = last[aux];
    }
    reverse(ans.begin(), ans.end());

    printf("%d\n", n - ans.size());
    for (int i = 0; i < ans.size(); i++) {
        if (i) printf(" ");
        printf("%d", ans[i]);
    }
    printf("\n");

    return 0;
}
