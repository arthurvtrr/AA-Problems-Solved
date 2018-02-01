#include <bits/stdc++.h>

using namespace std;

int t, n, q, x, bin[100100];
char op;
long long quant;

struct TrieNode {
    TrieNode *child[2], *parent;
    int h[2], ph;

    TrieNode() {
        child[0] = child[1] = parent = NULL;
        h[0] = h[1] = ph = -1;
    }
};

TrieNode *root, *lst;

void print(TrieNode *aux, int h, int val) {
    printf("%d %d\n", h, val);
    if (aux->child[0]) print(aux->child[0], h + aux->h[0], 0);
    if (aux->child[1]) print(aux->child[1], h + aux->h[1], 1);
}

TrieNode* getpos(int lft) {
    TrieNode *aux = lst;

    while (aux->ph != -1 && aux->ph <= lft) {
        lft -= aux->ph;
        aux = aux->parent;
    }

    if (lft != 0) {
        TrieNode *p = aux->parent, *nw = new TrieNode();
        nw->child[0] = aux;
        nw->h[0] = lft;
        nw->child[0]->ph = lft;
        nw->child[0]->parent = nw;

        p->h[0] -= lft;
        nw->ph = p->h[0];
        nw->parent = p;
        p->child[0] = nw;

        aux = p->child[0];
    }

    return aux;
}

void add(int pos, int fim) {
    TrieNode *aux;

    if (pos != n+1) {
        aux = getpos(pos);

        if (!aux->child[1]) {
            aux->child[1] = new TrieNode();
            aux->h[1] = 1;
            aux->child[1]->ph = 1;
            aux->child[1]->parent = aux;
            quant++;
        }
        aux = aux->child[1];
    }
    else {
        aux = getpos(n);
    }

    int atual = pos - 2;
    while (atual >= fim) {
        if (!aux->child[0]) {
            aux->child[0] = new TrieNode();
            aux->h[0] = 1;
            aux->child[0]->ph = 1;
            aux->child[0]->parent = aux;
            quant++;
        }
        aux = aux->child[0];
        atual -= aux->ph;
    }

    while (atual >= 0 && aux->child[bin[atual]]) {
        aux = aux->child[bin[atual]];
        atual -= aux->ph;
    }

    quant += atual+1;
    if (atual >= 0) {
        TrieNode *toadd = getpos(atual);
        memcpy(&aux->child[bin[atual]], &toadd, sizeof(&toadd));
        aux->child[bin[atual]]->parent = aux;
        aux->h[bin[atual]] = aux->child[bin[atual]]->ph = 1;
    }

    lst = aux;
    while (atual >= 0) {
        lst = lst->child[bin[atual]];
        atual -= lst->ph;
    }
}

void init(int x) {
    TrieNode *aux;
    if (n - x - 1 > 0) {
        root->child[0] = new TrieNode();
        root->h[0] = n - x - 1;
        root->child[0]->ph = n - x - 1;
        root->child[0]->parent = root;
        aux = root->child[0];
    }
    else aux = root;

    aux->child[1] = new TrieNode();
    aux->h[1] = 1;
    aux->child[1]->ph = 1;
    aux->child[1]->parent = aux;
    aux = aux->child[1];

    if (x == 0) lst = aux;
    else {
        lst = new TrieNode();
        aux->child[0] = lst;
        aux->h[0] = x; lst->ph = x;
        lst->parent = aux;
    }
}

int main() {
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &n, &q);

        memset(bin, 0, sizeof bin);
        root = new TrieNode();

        quant = 1;
        bool first = true;

        for (int i = 0; i < q; i++) {
            scanf(" %c", &op);

            if (op == '!') {
                scanf("%d", &x);

                if (first) {
                    init(x);
                    first = false;
                    quant += n;
                }
                else {
                    int aux = x;
                    while (bin[aux] != 0 && aux < n) aux++;
                    add(aux+1, x);
                }

                while (bin[x] != 0 && x < n) bin[x++] = 0;
                bin[x] = 1;
            }
            else printf("%lld\n", quant);
        }
    }
    return 0;
}
