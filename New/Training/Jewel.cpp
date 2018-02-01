#include <stdio.h>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

struct Node {
    int acum;
    Node *left, *right;

    Node(int acum, Node *left, Node *right) : acum(acum), left(left), right(right) {}

    Node* update(int ini, int fim, int pos);
};

Node *null = new Node(0, NULL, NULL);

Node* Node::update(int ini, int fim, int pos) {
    if (ini > pos || fim < pos) return this;

    if (ini == fim)
        return new Node(1, null, null);

    int meio = (ini + fim) / 2;

    return new Node(this->acum + 1, this->left->update(ini, meio, pos), this->right->update(meio+1, fim, pos));
}

int query(int ini, int fim, int k, Node *a, Node *b) {
    if (ini == fim)
        return ini;

    int meio = (ini + fim) / 2;

    int rank_ = a->left->acum - b->left->acum;
    if (rank_ >= k)
        return query(ini, meio, k, a->left, b->left);

    return query(meio+1, fim, k - rank_, a->right, b->right);
}

int n, x, y, z, nums[100100], ranks[100100];
char op[10];
map < int, int > ord;

Node *root[100100];

struct query {
    int type;
    int a, b, c;
} queries[300000];

int bit[100100];

void bitUpdate(int pos, int val) {
    while (pos < 100100) {
        bit[pos] += val;
        pos += pos & -pos;
    }
}

int bitQuery(int pos) {
    int ret = 0;
    while (pos) {
        ret += bit[pos];
        pos -= pos & -pos;
    }
    return ret;
}

int main() {
    int test = 1;
    while (scanf("%d", &n) != EOF) {

        for (int i = 0; i < 100100; i++) {
            root[i] = null;
            nums[i] = ranks[i] = bit[i] = 0;
        }
        ord.clear();

        int ind = 1;

        for (int i = 1; i <= n; i++) {
            scanf("%s", op);
            if (op[0] == 'I') {
                scanf("%d", &nums[ind]);
                queries[i].type = 1;
                queries[i].a = nums[ind];
                ord[nums[ind]];
                ind++;
            }
            else if (op[6] == '1') {
                scanf("%d %d %d", &queries[i].a, &queries[i].b, &queries[i].c);
                queries[i].type = 2;
            }
            else if (op[6] == '2') {
                scanf("%d", &queries[i].a);
                queries[i].type = 3;
            }
            else {
                scanf("%d", &queries[i].a);
                queries[i].type = 4;
            }
        }

        ind = 1;
        for (map < int, int >::iterator it = ord.begin(); it != ord.end(); it++) {
            ord[it->first] = ind;
            ranks[ind++] = it->first;
        }

        root[0] = null;
        root[0]->left = root[0]->right = null;

        int cont = 1;
        long long q1 = 0, q2 = 0, q3 = 0;

        for (int i = 1; i <= n; i++) {
            if (queries[i].type == 1) {
                root[cont] = root[cont-1]->update(1, ind-1, ord[nums[cont]]);
                bitUpdate(ord[nums[cont]], 1);
                cont++;
            }
            else if (queries[i].type == 2) {
                int pos = query(1, ind-1, queries[i].c, root[queries[i].b], root[queries[i].a-1]);
                q1 += ranks[pos];
            }
            else if (queries[i].type == 3) {
                q2 += bitQuery(ord[queries[i].a]);
            }
            else {
                int pos = query(1, ind-1, queries[i].a, root[cont-1], root[0]);
                q3 += ranks[pos];
            }
        }

        printf("Case %d:\n%lld\n%lld\n%lld\n", test++, q1, q2, q3);
    }
    return 0;
}
