#include <bits/stdc++.h>

using namespace std;

#define N 200100
#define LOGN 50

//Suffix Array + LCP

struct suffix {
    int index;
    int rank[2];
} suffixes[N];

int ind[N], suffixArr[N], lcp[N], invSuff[N];

int cmp(struct suffix a, struct suffix b) {
    if (a.rank[0] == b.rank[0])
        return a.rank[1] < b.rank[1];
    return a.rank[0] < b.rank[0];
}

void buildSuffixArray(string txt, int n) {
    for (int i = 0; i < n; i++) {
        suffixes[i].index = i;
        suffixes[i].rank[0] = txt[i] - 'a';
        suffixes[i].rank[1] = ((i+1) < n)? (txt[i + 1] - 'a'): -1;
    }

    sort(suffixes, suffixes+n, cmp);

    for (int k = 4; k < 2*n; k = k*2) {
        int rank = 0;
        int prev_rank = suffixes[0].rank[0];
        suffixes[0].rank[0] = rank;
        ind[suffixes[0].index] = 0;

        for (int i = 1; i < n; i++) {
            if (suffixes[i].rank[0] == prev_rank && suffixes[i].rank[1] == suffixes[i-1].rank[1]) {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = rank;
            }
            else {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = ++rank;
            }
            ind[suffixes[i].index] = i;
        }

        for (int i = 0; i < n; i++) {
            int nextindex = suffixes[i].index + k/2;
            suffixes[i].rank[1] = (nextindex < n)? suffixes[ind[nextindex]].rank[0]: -1;
        }

        sort(suffixes, suffixes+n, cmp);
    }

    for (int i = 0; i < n; i++)
        suffixArr[i] = suffixes[i].index;
}

void kasai(string txt, int n) {
    for (int i = 0; i < n; i++)
        invSuff[suffixArr[i]] = i;

    int k = 0;

    for (int i = 0; i < n; i++) {
        if (invSuff[i] == n-1) {
            k = 0;
            continue;
        }

        int j = suffixArr[invSuff[i]+1];

        while (i+k<n && j+k<n && txt[i+k]==txt[j+k] && txt[i+k] != ' ' && txt[j+k] != ' ')
            k++;

        lcp[invSuff[i]] = k;

        if (k > 0) k--;
    }
}

//RMQ

int rmq[N][LOGN], LOG[N];

void processRMQ() {
    for (int i = 0, ret = 0; i < N; i++)
        LOG[i] = ret += (i > 1 && !(i&(i-1)));

    for (int i = 0; i < N; i++)
        rmq[i][0] = i;

    for (int j = 1; 1 << j < N; j++)
        for (int i = 0; i + (1 << j) - 1 < N; i++)
            if (lcp[rmq[i][j - 1]] < lcp[rmq[i + (1 << (j - 1))][j - 1]])
                rmq[i][j] = rmq[i][j - 1];
            else
                rmq[i][j] = rmq[i + (1 << (j - 1))][j - 1];
}

int RMQquery(int i, int j) {
    int k = LOG[j - i + 1];
    return min(lcp[rmq[i][k]], lcp[rmq[j - (1 << k) + 1][k]]);
}

//Persistent Segtree

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

//Rest

int n, k, siz, num[N], ini[N];
long long ans[N];
string words[N];

bool possible(int x, int i) {
    int ini = 0, fim = i-1;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        if (RMQquery(meio, i-1) < x) ini = meio+1;
        else fim = meio-1;
    }
    int l = ini;

    ini = i+1, fim = siz;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        if (RMQquery(i, meio-1) < x) fim = meio-1;
        else ini = meio+1;
    }
    int r = fim;
    if (RMQquery(i, fim) >= x) r++;

    return persQuery(1, siz, l+1, r+1, root[r+1]) >= k;
}

int main() {
    string s = "";
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; i++)
        cin >> words[i];

    int cont = 0, charc = 200;
    siz = 0;
    for (int i = 0; i < n; i++) {
        ini[i+1] = cont;
        siz += words[i].size();
        for (int j = 0; j < words[i].size(); j++) {
            s += words[i][j];
            num[cont++] = i+1;
        }
        s += ' ';
        siz++;
        num[cont++] = 0;
    }

    if (k == 1) {
        for (int i = 0; i < n; i++) {
            if (i) printf(" ");
            long long x = words[i].size();
            printf("%lld", x * (x+1) / 2);
        }
        printf("\n");
    }
    else {
        buildSuffixArray(s, siz);
        kasai(s, siz);
        processRMQ();

        for (int i = 0; i < N; i++)
            lastPos[i] = -1;

        for (int i = 0; i < N; i++)
            root[i] = null;
        root[0]->left = root[0]->right = null;

        for (int i = 0; i < siz; i++) {
            root[i+1] = root[i]->update(1, siz, i+1, 1);
            if (lastPos[num[suffixArr[i]]] != -1)
                root[i+1] = root[i+1]->update(1, siz, lastPos[num[suffixArr[i]]], -1);
            lastPos[num[suffixArr[i]]] = i+1;
        }

        for (int i = n; i < siz; i++) {
            int ini = 1, fim = N;
            while (ini <= fim) {
                int meio = (ini + fim) / 2;
                if (possible(meio, i)) ini = meio+1;
                else fim = meio-1;
            }
            ans[num[suffixArr[i]]] += fim;
        }

        for (int i = 1; i <= n; i++) {
            if (i > 1) printf(" ");
            printf("%lld", ans[i]);
        }
        printf("\n");
    }

    return 0;
}

