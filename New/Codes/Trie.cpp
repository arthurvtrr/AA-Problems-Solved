#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int n;
string s;

#define ALPHABET_SIZE 20

struct TrieNode {
    TrieNode *child[ALPHABET_SIZE];
    bool isLeaf = false;

    TrieNode() {
        for (int i = 0; i < ALPHABET_SIZE; i++)
            child[i] = NULL;
    }
};

void insertWord(TrieNode *root, string s) {
    TrieNode *aux = root;

    for (int level = 0; level < s.size(); level++) {
        if (!aux->child[s[level] - '0'])
            aux->child[s[level] - '0'] = new TrieNode();

        aux = aux->child[s[level] - '0'];
    }

    aux->isLeaf = true;
}

bool searchWord(TrieNode *root, string s) {
    TrieNode *aux = root;

    for (int level = 0; level < s.size(); level++) {
        int index = s[level] - '0';

        if (!aux->child[index]) return false;

        aux = aux->child[index];
    }

    return (aux != NULL && aux->isLeaf);
}

int main() {
    TrieNode *root = new TrieNode();

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        cin >> s;
        insertWord(root, s);
    }
    printf("%d\n", searchWord(root, s));

    return 0;
}
