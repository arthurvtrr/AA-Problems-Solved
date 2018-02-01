#include <bits/stdc++.h>

using namespace std;

int n, m, a, b, x, y, quanta[100100];
vector < int > graph[100100];

struct node {
    int ind;
    bool operator <(node other) const {
        if (quanta[ind] == quanta[other.ind]) return ind < other.ind;
        return quanta[ind] < quanta[other.ind];
    }
};

int main() {
    while (scanf("%d %d %d %d", &n, &m, &a, &b) != EOF) {
        for (int i = 0; i <= n; i++)
            graph[i].clear();

        for (int i = 0; i < m; i++) {
            scanf("%d %d", &x, &y);
            graph[x].push_back(y);
            graph[y].push_back(x);
        }

        for (int i = 1; i <= n; i++)
            quanta[i] = graph[i].size();

        set < node > aux;
        for (int i = 1; i <= n; i++)
            aux.insert((node){i});

        while (!aux.empty()) {
            node atual = *aux.begin();
            if (quanta[atual.ind] < a) {
                aux.erase(aux.begin());

                for (int v : graph[atual.ind]) {
                    if (aux.count((node){v})) {
                        aux.erase(aux.find((node){v}));
                        quanta[v]--;
                        aux.insert((node){v});
                    }
                }
            }
            else break;
        }

        while (!aux.empty()) {
            node atual = *aux.rbegin();
            if (aux.size() - quanta[atual.ind] - 1 < b) {
                aux.erase(aux.find((node){atual.ind}));

                for (int v : graph[atual.ind])
                    if (aux.count((node){v})) {
                        aux.erase(aux.find((node){v}));
                        quanta[v]--;
                        aux.insert((node){v});
                    }
            }
            else break;
        }

        printf("%d\n", aux.size());
    }

    return 0;
}
