#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>
#include <map>

using namespace std;

struct Node {
    int maxi, lmaxi, rmaxi;
    Node *left, *right;

    Node(int m, int l, int r, Node *left, Node *right) :
    maxi(m), lmaxi(l), rmaxi(r), left(left), right(right) {}

    Node* update(int ini, int fim, int pos);
};

Node *null = new Node(0, 0, 0, NULL, NULL);

Node* Node::update(int ini, int fim, int pos) {
    if (ini > pos || fim < pos) return this;

    if (ini == fim)
        return new Node(1, 1, 1, null, null);

    int meio = (ini + fim) / 2;

    Node *ret = new Node(0, 0, 0, this->left->update(ini, meio, pos), this->right->update(meio+1, fim, pos));

    ret->maxi = max(ret->left->maxi, max(ret->right->maxi, ret->left->rmaxi + ret->right->lmaxi));

    ret->lmaxi = ret->left->lmaxi;
    if (ret->left->lmaxi == meio - ini + 1)
        ret->lmaxi += ret->right->lmaxi;

    ret->rmaxi = ret->right->rmaxi;
    if (ret->right->rmaxi == fim - meio)
        ret->rmaxi += ret->left->rmaxi;

    return ret;
}

struct data {
    int maxi, lmaxi, rmaxi;
};

data query(Node *atual, int ini, int fim, int start, int end) {
    if (ini > end || fim < start)
        return (data) {0, 0, 0};
    if (start <= ini && end >= fim)
        return (data) {atual->maxi, atual->lmaxi, atual->rmaxi};

    int meio = (ini + fim) / 2;

    data l = query(atual->left, ini, meio, start, end);
    data r = query(atual->right, meio+1, fim, start, end);

    data ret = (data) {0, 0, 0};

    ret.maxi = max(l.maxi, max(r.maxi, l.rmaxi + r.lmaxi));

    ret.lmaxi = l.lmaxi;
    if (l.lmaxi == meio - ini + 1)
        ret.lmaxi += r.lmaxi;

    ret.rmaxi = r.rmaxi;
    if (r.rmaxi == fim - meio)
        ret.rmaxi += l.rmaxi;

    return ret;
}

struct num {
    int val;
    int pos;
} nums[100100];

bool cmp(num a, num b) {
    return a.val > b.val;
}

int n, m, x, y, z;
Node *root[100100];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &nums[i].val);
        nums[i].pos = i;
    }

    sort(nums+1, nums+n+1, cmp);

    root[0] = null;
    root[0]->left = root[0]->right = null;

    for (int i = 1; i <= n; i++)
        root[i] = root[i-1]->update(1, n, nums[i].pos);

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &x, &y, &z);

        int ini = 1, fim = n;
        while (ini <= fim) {
            int mid = (ini + fim) / 2;

            if (query(root[mid], 1, n, x, y).maxi >= z) fim = mid-1;
            else ini = mid+1;
        }

        printf("%d\n", nums[ini]);
    }

    return 0;
}
