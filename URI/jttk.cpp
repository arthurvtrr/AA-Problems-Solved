#include <stdio.h>
#include <algorithm>
#include <queue>
#include <vector>
#include <time.h>
#include <iostream>

using namespace std;

#define pii pair < int, int >
#define INF 1000000000

int V[505][505], R[505][505], C[505][505];
int r, c, n2, x, y;
int dist[505][505], P[505][505];

struct Node {
    bool vis;
    int x;
    int y;
    Node(){
		vis=true;
	}
	Node(int _x, int _y, bool _vis) {
		x=_x; y=_y; vis=_vis;
	}
};

const int N=501;

Node t[2*N][2*N];

int n, m;

#define zero Node()
#define f(x,y) x.vis?y:x
#define apply(x,y) x=y

Node query(int x1, int y1, int x2, int y2) {
    x1 += n;
    x2 += n;
    y1 += m;
    y2 += m;
    Node res = zero;
    for (int lx = x1, rx = x2; lx <= rx; lx = (lx + 1) >> 1, rx = (rx - 1) >> 1)
      for (int ly = y1, ry = y2; ly <= ry; ly = (ly + 1) >> 1, ry = (ry - 1) >> 1) {
        if ((lx & 1) != 0 && (ly & 1) != 0) res = f(res, t[lx][ly]);
        if ((lx & 1) != 0 && (ry & 1) == 0) res = f(res, t[lx][ry]);
        if ((rx & 1) == 0 && (ly & 1) != 0) res = f(res, t[rx][ly]);
        if ((rx & 1) == 0 && (ry & 1) == 0) res = f(res, t[rx][ry]);
      }
    return res;
}

void upd(int x, int y, Node value) {
    x += n;
    y += m;
    apply(t[x][y], value);
    for (int tx = x; tx > 0; tx >>= 1)
      for (int ty = y; ty > 0; ty >>= 1) {
        if (tx > 1) t[tx >> 1][ty] = f(t[tx][ty], t[tx ^ 1][ty]);
        if (ty > 1) t[tx][ty >> 1] = f(t[tx][ty], t[tx][ty ^ 1]);
      }
}

int bfs(int x1, int y1, int x2, int y2) {
    if (x1 == x2 && y1 == y2) return 0;

    for (int i = 1; i <= r; i++)
        for (int j = 1; j <= c; j++) {
            dist[i][j] = INF;
            P[i][j] = 1;
        }

    priority_queue < pair < int, pii > > fila;
    dist[x1][y1] = V[x1][y1];
    fila.push(make_pair(-dist[x1][y1], make_pair(x1, y1)));
	for (int i=0; i<n; i++)
		for (int j=0; j<m; j++)
			upd(i, j, Node(i, j, false));
    upd(x1, y1, Node(x1, y1, true));
	int a1, b1, a2, b2;
    Node aux;
    while (!fila.empty()) {
        pii u = fila.top().second;
        fila.pop();
        if (abs(u.first - x2) <= R[u.first][u.second] && abs(u.second - y2) <= C[u.first][u.second]) return dist[u.first][u.second];

        a1 = max(1, u.first - R[u.first][u.second]);
        b1 = max(1, u.second - C[u.first][u.second]);
        a2 = min(r, u.first + R[u.first][u.second]);
        b2 = min(c, u.second + C[u.first][u.second]);

        while (1) {
            aux = query(a1, b1, a2, b2);
            if (aux.vis) break;

            dist[aux.x][aux.y] = dist[u.first][u.second] + V[aux.x][aux.y];
            fila.push(make_pair(-dist[aux.x][aux.y], make_pair(aux.x, aux.y)));
            upd(aux.x, aux.y, Node(aux.x, aux.y, true));
        }
    }
    return -1;
}

clock_t start;

int main() {
    start = clock();
    while (scanf("%d %d %d", &r, &c, &n2) != EOF) {
        for (int i = 0; i < 505; i++)
            for (int j = 0; j < 505; j++) {
                V[i][j] = 0;
                R[i][j] = 0;
                C[i][j] = 0;
            }
		n=r+1; m=c+1;
        for (int i = 1; i <= r; i++)
            for (int j = 1; j <= c; j++)
                scanf("%d", &V[i][j]);

        for (int i = 1; i <= r; i++)
            for (int j = 1; j <= c; j++)
                scanf("%d", &R[i][j]);

        for (int i = 1; i <= r; i++)
            for (int j = 1; j <= c; j++)
                scanf("%d", &C[i][j]);

        int lx, ly;
        for (int i = 0; i < n2; i++) {
            scanf("%d %d", &x, &y);
            if (i > 1) printf(" ");
            if (i > 0) printf("%d", bfs(lx, ly, x, y));
            lx = x;
            ly = y;
        }
        printf("\n");
    }

    cout << "Time: " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << endl;
    return 0;
}
