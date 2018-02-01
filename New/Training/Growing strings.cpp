#include <bits/stdc++.h>

using namespace std;

#define NULO -1

const int MAX_NO = 1000100;
const int MAX_PAD = 10100;

typedef map <char, int> mapach;
typedef map <string, int> mapastr;

mapach trans[MAX_NO];
mapastr pad;

vector < int > pos[MAX_PAD];
int falha[MAX_NO], final[MAX_NO], tam[MAX_PAD], numNos;

void inic() {
    memset(falha, NULO, sizeof(falha));
    memset(final, NULO, sizeof(final));
    for (int i = 0; i < numNos; i++) trans[i].clear();
    pad.clear(); numNos = 1;
}

int adiciona_padrao(string s) {
    pair <mapach::iterator, bool> pch;
    int i, no = 0, numPad = pad.size();

    if (pad.count(s)) return pad[s];
    else pad.insert(make_pair(s, numPad));

    for (i = 0; s[i]; i++) {
        if ((pch = trans[no].insert(make_pair(s[i], numNos))).second) numNos++;
        no = pch.first->second;
    }

    tam[numPad] = i ? i : 1;
    return final[no] = numPad;
}

void gera_falhas() {
    queue < int > fila;
    int filho;
    for (mapach::iterator it = trans[0].begin(); it != trans[0].end(); it++) {
        falha[filho = it->second] = 0;
        fila.push(filho);
    }

    while (!fila.empty()) {
        int atual = fila.front(); fila.pop();

        for (mapach::iterator it = trans[atual].begin(); it != trans[atual].end(); it++) {
            char c = it->first; filho = it->second; int ret = falha[atual];
            fila.push(filho);

            while (ret != NULO && !trans[ret].count(c))
                ret = falha[ret];

            if (ret == NULO) {
                if (trans[0].count(c)) falha[filho] = trans[0][c];
                else falha[filho] = 0;
            }
            else {
                falha[filho] = trans[ret][c];
                if (final[filho] == NULO && final[falha[filho]] != NULO)
                    final[filho] = final[falha[filho]];
            }
        }
    }
}

void consulta(string s) {
    int ret, atual = 0, i = 0;

    int N = pad.size();
    for (int j = 0; j < N; j++) pos[j].clear();

    do {
        while (atual != NULO && !trans[atual].count(s[i]))
            atual = falha[atual];
        atual = (atual == NULO)? 0 : trans[atual][s[i]];

        for (ret = atual; ret != NULO && final[ret] != NULO; ret = falha[ret]) {
            pos[final[ret]].push_back(i - tam[final[ret]] + 1);
            while (falha[ret] != NULO && final[falha[ret]] == final[ret])
                ret = falha[ret];
        }
    } while (s[i++]);
}

int n;
string pattern[10100];
int seqSiz[10100], ind[10100];

bool cmp(string a, string b) {
    return a.size() < b.size();
}

int main() {
    while (1) {
        scanf("%d", &n);
        if (n == 0) break;

        inic();

        for (int i = 0; i < n; i++)
            cin >> pattern[i];

        sort(pattern, pattern+n, cmp);

        for (int i = 0; i < n; i++)
            ind[i] = adiciona_padrao(pattern[i]);

        gera_falhas();

        int ans = 0;

        for (int i = 0; i < n; i++) {
            seqSiz[i] = 1;
            consulta(pattern[i]);

            for (int j = 0; j < i; j++)
                if (pos[ind[j]].size() > 0)
                    seqSiz[i] = max(seqSiz[i], seqSiz[j] + 1);

            ans = max(ans, seqSiz[i]);
        }

        printf("%d\n", ans);
    }

    return 0;
}

