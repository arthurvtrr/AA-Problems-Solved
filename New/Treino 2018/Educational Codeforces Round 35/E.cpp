#include <bits/stdc++.h>

using namespace std;

int n, k, nums[200200];
int bit[200200];

void update(int pos, int val) {
    while (pos < 200200) {
        bit[pos] += val;
        pos += pos & -pos;
    }
}

int query(int pos) {
    int ret = 0;
    while (pos) {
        ret += bit[pos];
        pos -= pos & -pos;
    }
    return ret;
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < k; i++)
        scanf("%d", &nums[i]);

    stack < int > pilha;
    int nxt = 1;

    for (int i = 0; i < k; i++) {
        if (query(nums[i])) {
            printf("-1\n");
            exit(0);
        }

        pilha.push(nums[i]);
        update(nums[i], 1);

        while (!pilha.empty() && pilha.top() == nxt) {
            update(pilha.top(), -1);
            pilha.pop();
            nxt++;
        }
    }

    for (int i = k; i < n; i++) {
        int ini = 1, fim = n;
        while (ini <= fim) {
            int meio = (ini + fim) / 2;
            if (query(meio) == 0) ini = meio+1;
            else fim = meio-1;
        }

        nums[i] = fim;
        pilha.push(nums[i]);
        update(nums[i], 1);

        while (!pilha.empty() && pilha.top() == nxt) {
            update(pilha.top(), -1);
            pilha.pop();
            nxt++;
        }
    }

    for (int i = 0; i < n; i++) {
        if (i) printf(" ");
        printf("%d", nums[i]);
    }
    printf("\n");

    return 0;
}
