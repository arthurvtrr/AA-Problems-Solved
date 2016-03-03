#include <stdio.h>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

int pos_next_g[110000], pos_last_g[110000], alt[110000], seg[440000];

void next_g(int n) {
    for (int i = 1; i <= n; i++)
        pos_next_g[i] = -1;
    stack < int > aux;
    for (int i = 1; i <= n; i++) {
        while (!aux.empty() && alt[i] > alt[aux.top()]) {
            pos_next_g[aux.top()] = i;
            aux.pop();
        }
        aux.push(i);
    }
}

void last_g(int n) {
    for (int i = 1; i <= n; i++)
        pos_last_g[i] = -1;
    stack < int > aux;
    for (int i = n; i >= 1; i--) {
        while (!aux.empty() && alt[i] > alt[aux.top()]) {
            pos_last_g[aux.top()] = i;
            aux.pop();
        }
        aux.push(i);
    }
}

void build(int id, int ini, int fim) {
    if (ini == fim) {
        seg[id] = alt[ini];
        return;
    }
    int meio = (ini + fim) / 2;
    build(2*id, ini, meio);
    build(2*id+1, meio+1, fim);
    seg[id] = min(seg[2*id], seg[2*id+1]);
}

int query(int id, int ini, int fim, int start, int end) {
    if (end < start) return 99999999;
    if (end < ini || start > fim) return 99999999;
    if (ini >= start && fim <= end) return seg[id];
    int meio = (ini + fim) / 2;
    return min(query(2*id, ini, meio, start, end), query(2*id+1, meio+1, fim, start, end));
}

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        vector < int > ultras;
        for (int i = 1; i <= n; i++)
            scanf("%d", &alt[i]);
        next_g(n);
        last_g(n);
        build(1, 1, n);
        for (int i = 1; i <= n; i++) {
            int minim = -1;
            if (pos_next_g[i] != -1)
                minim = max(minim, query(1, 1, n, i+1, pos_next_g[i]-1));
            if (pos_last_g[i] != -1)
                minim = max(minim, query(1, 1, n, pos_last_g[i]+1, i-1));

            if (minim == -1 && alt[i] >= 150000)
                ultras.push_back(i);
            else if (alt[i] - minim >= 150000) ultras.push_back(i);
        }
        for (int i = 0; i < ultras.size(); i++) {
            if (i > 0) printf(" ");
            printf("%d", ultras[i]);
        }
        printf("\n");
    }
    return 0;
}
