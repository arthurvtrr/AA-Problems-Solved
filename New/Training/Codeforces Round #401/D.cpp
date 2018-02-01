#include <bits/stdc++.h>

using namespace std;

int n;
string hashs[500500];
vector < bool > print[500500];

#define ALPHABET_SIZE 27

struct TrieNode {
    TrieNode *child[ALPHABET_SIZE];
    bool isLeaf = false;
    vector < int > words;

    TrieNode() {
        for (int i = 0; i < ALPHABET_SIZE; i++)
            child[i] = NULL;
    }
};

TrieNode *root;

void dfs(TrieNode *aux, int lvl) {
    for (int v : aux->words)
        print[v][lvl] = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (aux->child[i])
            dfs(aux->child[i], lvl+1);
}

void insertWord(TrieNode *root, string s, int ind) {
    TrieNode *aux = root;

    for (int level = 1; level < s.size(); level++) {
        int pos = s[level] - 'a';

        bool removed = false;
        for (int i = pos+1; i < ALPHABET_SIZE; i++) {
            if (aux->child[i]) {
                removed = true;
                dfs(aux->child[i], level);
                aux->child[i] = NULL;
            }
        }

        if (removed) {
            for (int i = 0; i <= pos; i++)
                if (aux->child[i]) {
                    dfs(aux->child[i], level);
                    aux->child[i] = NULL;
                }
        }

        if (!aux->child[pos])
            aux->child[pos] = new TrieNode();

        aux = aux->child[pos];
        aux->words.push_back(ind);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (aux->child[i]) {
            dfs(aux->child[i], s.size());
            aux->child[i] = NULL;
        }

    aux->isLeaf = true;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        cin >> hashs[i];
        for (int j = 0; j < hashs[i].size(); j++)
            print[i].push_back(true);
    }

    root = new TrieNode();

    for (int i = 0; i < n; i++)
        insertWord(root, hashs[i], i);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < print[i].size(); j++)
            if (print[i][j])
                printf("%c", hashs[i][j]);
        printf("\n");
    }

    return 0;
}

