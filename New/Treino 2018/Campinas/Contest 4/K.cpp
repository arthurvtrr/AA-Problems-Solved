#include <bits/stdc++.h>

using namespace std;

vector < string > words;
string s;
set < string > dif;
map < string, int > ind;
string orig[4040];

struct node {
    node* child[30];
    set < int > l;

    int cnt, lst;
    node() {
        cnt = 0; lst = -1;
        for (int i = 0; i < 30; i++)
            child[i] = NULL;
        l.clear();
    }
} *root;

void insertWord(int pos) {
    node *aux = root;
    for (int i = pos; i < words.size(); i++) {
        if (!aux->child[words[i][0] - 'a'])
            aux->child[words[i][0] - 'a'] = new node();
        aux = aux->child[words[i][0] - 'a'];
        if (aux->l.size() <= 1) aux->l.insert(ind[words[i]]);
        if (aux->lst < pos) aux->cnt++;
        aux->lst = i;
    }
}

string best;
int ans;

void solve(node *aux, string x, int siz, bool v) {
    int val = siz*(aux->cnt-1) - ((int)x.size())*aux->cnt;

    if (v && val > ans && !dif.count(x)) {
        ans = val;
        best = x;
    }

    for (int i = 0; i < 30; i++) {
        for (int v : aux->child[i]->l) {
            solve(aux->child[i], x + orig[v][0], siz + orig[v].size(), root->child[i]->l.size() == 1);
        }
    }
}

int main() {
    //freopen("kina.in", "r", stdin);
    //freopen("kina.out", "w", stdout);

    while (cin >> s) {
        string aux = "";
        for (int i = 0; i < s.size(); i++) {
            if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')) {
                aux += tolower(s[i]);
            }
            else {
                if (!aux.empty()) words.push_back(aux);
                aux = "";
            }
        }
        if (!aux.empty()) words.push_back(aux);
    }

    for (int i = 0; i < words.size(); i++)
        dif.insert(words[i]);

    int cnt = 1;
    for (string x : dif) {
        ind[x] = cnt;
        orig[cnt++] = x;
    }

    root = new node();

    for (int i = 0; i < words.size(); i++)
        insertWord(i);

    ans = 0;
    for (int i = 0; i < 30; i++) {
        for (int v : root->child[i]->l) {
            string ini = "";
            ini += orig[v][0];
            solve(root->child[i], ini, orig[v].size(), root->child[i]->l.size() == 1);
        }
    }

    printf("%d\n", ans);
    if (ans != 0) {
        for (int i = 0; i < best.size(); i++)
            printf("%c", toupper(best[i]));
        printf("\n");
    }

    return 0;
}
