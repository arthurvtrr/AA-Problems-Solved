#include <bits/stdc++.h>

using namespace std;

const int N = 300100;

struct Node {
    int val = -1;
    vector < int > child;
} trie[12*N];

int nxt, ind[300], tim[N];
vector < string > valor;

int index(int p, int el) {
    for (int i = 0; i < trie[p].child.size(); i++)
        if (trie[p].child[i] / 10000000 == el)
            return i;
    return -1;
}

void insertWord(int nw, int p, string s, int pv) {
    for (int i = 0; i < s.size(); i++) {
        trie[nw] = trie[p];

        int x = index(nw, ind[s[i]]);
        if (x == -1) trie[nw].child.push_back(ind[s[i]] * 10000000 + nxt);
        else trie[nw].child[x] = ind[s[i]] * 10000000 + nxt;

        nw = nxt++;

        x = index(p, ind[s[i]]);
        if (x == -1) p = 10*N-10;
        else p = trie[p].child[x] % 10000000;
    }

    trie[nw] = trie[p];
    trie[nw].val = pv;
}

#define pss pair < string, string >

vector<int> graph[N];
vector < pss > words[N];

void dfs(int u, int p) {
    tim[u] = nxt++;

    if (words[u].empty()) insertWord(tim[u], u == 0? 0 : tim[p], "", -1);
    else {
        insertWord(tim[u], u == 0? 0 : tim[p], words[u][0].first, valor.size());
        valor.push_back(words[u][0].second);
    }

    for (int i = 1; i < words[u].size(); i++) {
        int prv = tim[u];
        tim[u] = nxt++;
        insertWord(tim[u], prv, words[u][i].first, valor.size());
        valor.push_back(words[u][i].second);
    }

    for (int v : graph[u])
        if (v != p)
            dfs(v, u);
}

string solve(int u, string key) {
    int aux = tim[u];

    for (int i = 0; i < key.size(); i++) {
        int x = index(aux, ind[key[i]]);
        if (x == -1) return "N/A";
        aux = trie[aux].child[x] % 10000000;
    }
    return trie[aux].val == -1? "N/A" : valor[trie[aux].val];
}

const int MAX = 22;

char buffer[MAX];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int p, k;
        scanf("%d %d", &p, &k); --p;
        graph[i].push_back(p);
        graph[p].push_back(i);
        while (k--) {
            scanf("%s", buffer);
            string property = string(buffer);
            int equal_pos = property.find("=");
            words[i].push_back(pss(property.substr(0, equal_pos), property.substr(equal_pos + 1, property.size() - equal_pos)));
        }
    }

    int cnt = 0;
    for (char c = 'a'; c <= 'z'; c++)
        ind[c] = cnt++;
    for (char c = 'A'; c <= 'Z'; c++)
        ind[c] = cnt++;
    for (char c = '0'; c <= '9'; c++)
        ind[c] = cnt++;

    nxt = 1;
    dfs(0, -1);

    int q, u;
    scanf("%d", &q);
    while (q--) {
        scanf("%d %s", &u, buffer);
        string key = string(buffer);
        printf("%s\n", solve(u - 1, key).c_str());
        fflush(stdout);
    }
    return 0;
}
