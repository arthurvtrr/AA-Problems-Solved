#include <bits/stdc++.h>

using namespace std;

#define N 200100

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

