#include <bits/stdc++.h>

using namespace std;

#define N 300300
#define ALP_SIZ 26

struct Automaton {
    int nodes, fail[N], wid[N], endLink[N], child[N][ALP_SIZ];
    queue < int > q;
    bool leaf[N];

    int newnode() {
        fail[nodes] = wid[nodes] = endLink[nodes] = leaf[nodes] = 0;
        memset(child[nodes], 0, sizeof(child[nodes]));
        return nodes++;
    }

    void clear() {
        nodes = 0;
        newnode();
    }

    void insert(string s, int id) {
        int atual = 0;
        for (int i = 0; i < s.size(); i++) {
            int c = s[i] - 'a';
            if (!child[atual][c])
                child[atual][c] = newnode();
            atual = child[atual][c];
        }
        leaf[atual] = true;
        wid[atual] = id;
    }

    void getFails() {
        for (int i = 0; i < ALP_SIZ; i++)
            if (child[0][i]) {
                fail[child[0][i]] = 0, q.push(child[0][i]);
                if (leaf[child[0][i]]) endLink[child[0][i]] = child[0][i];
            }

        while (!q.empty()) {
            int u = q.front(); q.pop();

            for (int i = 0; i < ALP_SIZ; i++) {
                int v = child[u][i];
                if (!v) { child[u][i] = child[fail[u]][i]; continue; }

                q.push(v);
                int j = fail[u];
                while (j && !child[j][i]) j = fail[j];
                fail[v] = child[j][i];

                if (leaf[v]) endLink[v] = v;
                else endLink[v] = endLink[fail[v]];
            }
        }
    }
} AC;

int n;
string pat[N], s;

void findOccurs(string s) {
    int atual = 0;

    for (int i = 0; i < s.size(); i++) {
        while (!AC.child[atual][s[i] - 'a'] && atual != 0) atual = AC.fail[atual];
        atual = AC.child[atual][s[i] - 'a'];

        int aux = atual;
        while (true) {
            aux = AC.endLink[aux];
            if (aux == 0) break;

            cout << pat[AC.wid[aux]] << " found at position " << i - pat[AC.wid[aux]].size() + 1 << endl;

            aux = AC.fail[aux];
        }
    }
}

int main() {
    AC.clear();

    scanf("%d", &n); //numero de padroes
    for (int i = 0; i < n; i++) {
        cin >> pat[i];
        AC.insert(pat[i], i);
    }
    AC.getFails();

    getchar();
    getline(cin, s);
    findOccurs(s);
}
