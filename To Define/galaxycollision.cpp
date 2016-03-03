#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <vector>
#include <queue>
#include <set>

using namespace std;

#define pii pair < int, int >

vector < int > graph[50500];
vector < pii > pos[505000];
int n, sol;
bool visited[50500];
int dist[50500], groups[5];

void connect(int x) {
    int d;
	for (int i = pos[x].size() - 1; i >= 0; i--) {
		int y = pos[x][i].first, u = pos[x][i].second;
		for (int j = x - 5; j <= x + 5; j++) {
			if (j < 0) continue;
			int aux = (int)(lower_bound(pos[j].begin(), pos[j].end(), make_pair(y-5,-1)) - pos[j].begin());
			for (int k = aux; k < pos[j].size(); k++) {
				if (pos[j][k].first > y + 5) break;
				d = (x-j) * (x-j) + (pos[j][k].first - y) * (pos[j][k].first - y);
				if (d <= 25 && u != pos[j][k].second)
                    graph[u].push_back(pos[j][k].second);
			}
		}
	}
}

int bfs(int ini) {
    queue < int > fila;
    fila.push(ini);
    dist[ini] = 1;
    visited[ini] = true;
    groups[0] = 0;
    groups[1] = 0;

    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();
        groups[dist[u]&1]++;

        for (int v : graph[u])
            if (!visited[v]) {
                dist[v] = dist[u] + 1;
                visited[v] = true;
                fila.push(v);
            }
    }

    return min(groups[0], groups[1]);
}

int main() {
    int x, y;
    while (scanf("%d", &n) != EOF) {
        sol = 0;
        set < int > posis;
        for (int i = 0; i < 50500; i++) graph[i].clear();
        memset(visited, false, sizeof visited);

        for (int i = 0; i < n; i++) {
            scanf("%d %d", &x, &y);
            pos[x].push_back(make_pair(y,i));
            posis.insert(x);
        }

        for (set < int >::iterator it = posis.begin(); it != posis.end(); it++)
            sort (pos[*it].begin(), pos[*it].end());

        for (set < int >::iterator it = posis.begin(); it != posis.end(); it++)
            connect(*it);

        for (int i = 0; i < n; i++)
            if (!visited[i])
                sol += bfs(i);

        printf("%d\n", sol);

        for (set < int >::iterator it = posis.begin(); it != posis.end(); it++)
            pos[*it].clear();
    }
    return 0;
}
