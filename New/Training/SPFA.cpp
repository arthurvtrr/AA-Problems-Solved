#include <bits/stdc++.h>

using namespace std;

#define INF LLONG_MAX
#define ll long long
#define pll pair < ll, int >

int n, x, y;
ll dist[10000100];
bool inqueue[10000100];

ll SPFA(int node) {
	for(int i=0;i<10000100;i++)
		dist[i] = INF;

	dist[node] = 0;

	queue <int> fila;
	fila.push(node);
	inqueue[node] = 1;

	while(!fila.empty()) {
		int u = fila.front();
		fila.pop();
		inqueue[u] = 0;

		if (u % 2 == 0 && u > 0 && dist[u/2] > dist[u] + y) {
            dist[u/2] = dist[u] + y;
            if (!inqueue[u/2]) {
                fila.push(u/2);
                inqueue[u/2] = 1;
            }
        }
        if (u > 0 && dist[u-1] > dist[u] + x) {
            dist[u-1] = dist[u] + x;
            if (!inqueue[u-1]) {
                fila.push(u-1);
                inqueue[u-1] = 1;
            }
        }
        if (u+1 < 10000100 && dist[u+1] > dist[u] + x) {
            dist[u+1] = dist[u] + x;
            if (!inqueue[u+1]) {
                fila.push(u+1);
                inqueue[u+1] = 1;
            }
        }
	}

	return dist[0];
}

int main() {
    scanf("%d %d %d", &n, &x, &y);
    printf("%lld\n", SPFA(n));

    return 0;
}
