#include <stdio.h>
#include <limits.h>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

#define INF 2000000000
#define N 5050

int nodes = N, ini, fim;
int dist[N], work[N];

struct Edge {
    int to, rev, used_flow, cap;

    Edge(int a, int b, int c, int d) {
        to = a; rev = b; used_flow = c; cap = d;
    }
};

vector < Edge > graph[N];

void addEdge(int from, int to, int cap) {
    Edge a = Edge(to, graph[to].size(), 0, cap);
    Edge b = Edge(from, graph[from].size(), 0, 0);
    graph[from].push_back(a);
    graph[to].push_back(b);
}

bool dinic_bfs() {
    fill(dist, dist + nodes, -1);
    dist[ini] = 0;

    queue < int > fila;
    fila.push(ini);

    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();

        for (int i = 0; i < graph[u].size(); i++) {
            Edge &e = graph[u][i];
            int v = e.to;
            if (dist[v] < 0 && e.used_flow < e.cap) {
                dist[v] = dist[u] + 1;
                fila.push(v);
            }
        }
    }

    return dist[fim] >= 0;
}

int dinic_dfs(int u, int flow) {
    if (u == fim)
        return flow;

    for (int &i = work[u]; i < graph[u].size(); i++) {
        Edge &e = graph[u][i];

        if (e.cap > e.used_flow) {
            int v = e.to;

            if (dist[v] == dist[u] + 1) {
                int minf = dinic_dfs(v, min(flow, e.cap - e.used_flow));
                if (minf > 0) {
                    e.used_flow += minf;
                    graph[v][e.rev].used_flow -= minf;
                    return minf;
                }
            }
        }
    }

    return 0;
}

int flow(int _ini, int _fim) {
    ini = _ini;
    fim = _fim;
    int result = 0;

    while (dinic_bfs()) {
        fill(work, work + nodes, 0);
        while (int delta = dinic_dfs(ini, INT_MAX))
            result += delta;
    }

    return result;
}

#define ini 5048
#define fim 5049
#define AUX 2501

int ind[55][55];

class FoxAndGo3 {
    public:
        int maxEmptyCells(vector < string > board) {
            int n = board.size();
            int w_ind = 1, p_ind = AUX;

            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++) {
                    if (board[i][j] == 'o') {
                        ind[i][j] = w_ind;
                        addEdge(ini, w_ind++, 1);
                    }
                    else if (board[i][j] == '.') {
                        ind[i][j] = p_ind;
                        addEdge(p_ind++, fim, 1);
                    }
                }

            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++) {
                    if (i > 0 && board[i][j] == 'o' && board[i-1][j] == '.')
                        addEdge(ind[i][j], ind[i-1][j], INF/2);
                    if (i < n-1 && board[i][j] == 'o' && board[i+1][j] == '.')
                        addEdge(ind[i][j], ind[i+1][j], INF/2);
                    if (j > 0 && board[i][j] == 'o' && board[i][j-1] == '.')
                        addEdge(ind[i][j], ind[i][j-1], INF/2);
                    if (j < n-1 && board[i][j] == 'o' && board[i][j+1] == '.')
                        addEdge(ind[i][j], ind[i][j+1], INF/2);
                }

            return p_ind - AUX + (w_ind - 1 - flow(ini, fim));
        }
};
