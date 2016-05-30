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

int main() {
    TrieNode *root = new TrieNode();

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        cin >> s;
        insertWord(root, s);
    }

    return 0;
}

