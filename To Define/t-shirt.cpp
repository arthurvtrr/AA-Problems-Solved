#include <bits/stdc++.h>

using namespace std;

#define INF 1000000000

int flow(int ini, int fim, int n, vector < int > *graph, int **cap) {
    int answer = 0;
    int previous[n];
    bool used[n];

    while(true) {
        fill(used, used+n, false);
        fill(previous, previous+n, -1);

        queue < int > fila;
        fila.push(ini);

        while(!fila.empty()) {
            int u = fila.front();
            used[u] = true;
            fila.pop();

            for(int v : graph[u])
                if(!used[v] and cap[u][v] > 0) {
                    previous[v] = u;
                    fila.push(v);
                }
        }

        if (previous[fim] == -1) break;
        int minimum = INT_MAX, u = fim;

        while (previous[u] != -1) {
            minimum = min(cap[previous[u]][u], minimum);
            u = previous[u];
        }

        answer += minimum;
        u = fim;

        while (previous[u] != -1) {
            cap[previous[u]][u] -= minimum;
            cap[u][previous[u]] += minimum;
            u = previous[u];
        }
    }

    return answer;
}

#define ini 48
#define fim 49

int main() {
    int t, n, m;
    string a, b;
    map < string, int > ind = {{"XXL", 31}, {"XL", 32}, {"L", 33}, {"M", 34}, {"S", 35}, {"XS", 36}};
    scanf("%d", &t);

    for (int nt = 0; nt < t; nt++) {
        vector < int > connections[50];
        int **cap = new int*[50];
        for (int i = 0; i < 50; i++)
            cap[i] = new int[50];

        for (int i = 0; i < 50; i++)
            for (int j = 0; j < 50; j++)
                cap[i][j] = 0;

        scanf("%d %d", &n, &m);

        for (int i = 1; i <= m; i++) {
            cin >> a >> b;
            connections[i].push_back(ind[a]);
            connections[ind[a]].push_back(i);
            connections[i].push_back(ind[b]);
            connections[ind[b]].push_back(i);
            cap[i][ind[a]] = 1;
            cap[i][ind[b]] = 1;

            connections[ini].push_back(i);
            cap[ini][i] = 1;
        }

        for (int i = 31; i <= 36; i++) {
            connections[i].push_back(fim);
            cap[i][fim] = n / 6;
        }

        int s = flow(ini, fim, 50, connections, cap);
        if (s == m) printf("YES\n");
        else printf("NO\n");
    }

    return 0;
}
