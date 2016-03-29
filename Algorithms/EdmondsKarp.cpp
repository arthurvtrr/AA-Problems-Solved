#include <stdio.h>
#include <limits.h>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

#define INF 2000000000
#define N 250

int res[N][N];
vector < int > graph[N];

int flow(int ini, int fim, int n) {
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
                if(!used[v] and res[u][v] > 0) {
                    previous[v] = u;
                    fila.push(v);
                }
        }

        if (previous[fim] == -1) break;
        int minimum = INT_MAX, u = fim;

        while (previous[u] != -1) {
            minimum = min(res[previous[u]][u], minimum);
            u = previous[u];
        }

        answer += minimum;
        u = fim;

        while (previous[u] != -1) {
            res[previous[u]][u] -= minimum;
            res[u][previous[u]] += minimum;
            u = previous[u];
        }
    }

    return answer;
}
