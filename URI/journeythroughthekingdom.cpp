#include <stdio.h>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

#define pii pair < int, int >
#define INF 1000000000

int V[505][505], R[505][505], C[505][505];
int r, c, n, x, y;
int dist[505][505], P[505][505];

struct Node {
    int val;
    int x;
    int y;
};

Node Nmax(Node a, Node b) {
    if (a.val > b.val) return a;
    return b;
}

struct SegTree {
    Node seg[4*505][4*505];

    void init() {
        for (int i = 0; i < 4*505; i++)
            for (int j = 0; j < 4*505; j++)
                seg[i][j] = (Node) {0, 0, 0};
    }

    void build_y(int id_x, int ini_x, int fim_x, int id_y, int ini_y, int fim_y) {
        if (ini_y == fim_y)
            if (ini_x == fim_x)
                seg[id_x][id_y] = (Node) { P[ini_x][ini_y], ini_x, ini_y };
            else
                seg[id_x][id_y] = Nmax(seg[2*id_x][id_y], seg[2*id_x + 1][id_y]);
        else {
            int meio = (ini_y + fim_y) / 2;
            build_y(id_x, ini_x, fim_x, 2*id_y, ini_y, meio);
            build_y(id_x, ini_x, fim_x, 2*id_y + 1, meio+1, fim_y);
            seg[id_x][id_y] = Nmax(seg[id_x][2*id_y], seg[id_x][2*id_y + 1]);
        }
    }

    void build_x(int id_x, int ini_x, int fim_x) {
        if (ini_x != fim_x) {
            int meio = (ini_x + fim_x) / 2;
            build_x(2*id_x, ini_x, meio);
            build_x(2*id_x + 1, meio+1, fim_x);
        }
        build_y(id_x, ini_x, fim_x, 1, 1, c);
    }

    Node query_y(int id_x, int id_y, int tini_y, int tfim_y, int ini_y, int fim_y) {
        if (ini_y > fim_y)
            return (Node) { -INF, 0, 0 };
        if (ini_y == tini_y && tfim_y == fim_y)
            return seg[id_x][id_y];
        int tmeio = (tini_y + tfim_y) / 2;
        return Nmax(query_y(id_x, 2*id_y, tini_y, tmeio, ini_y, min(fim_y, tmeio)),
               query_y(id_x, 2*id_y + 1, tmeio+1, tfim_y, max(ini_y, tmeio+1), fim_y));
    }

    Node query_x(int id_x, int tini_x, int tfim_x, int ini_x, int fim_x, int ini_y, int fim_y) {
        if (ini_x > fim_x)
            return (Node) { -INF, 0, 0 };
        if (ini_x == tini_x && tfim_x == fim_x)
            return query_y(id_x, 1, 1, c, ini_y, fim_y);
        int tmeio = (tini_x + tfim_x) / 2;
        return Nmax(query_x(2*id_x, tini_x, tmeio, ini_x, min(fim_x, tmeio), ini_y, fim_y),
               query_x(2*id_x + 1, tmeio+1, tfim_x, max(ini_x, tmeio+1), fim_x, ini_y, fim_y));
    }

    void update_y(int id_x, int ini_x, int fim_x, int id_y, int ini_y, int fim_y, int x, int y, int new_val) {
        if (ini_y == fim_y) {
            if (ini_x == fim_x)
                seg[id_x][id_y] = (Node) { new_val, id_x, id_y };
            else
                seg[id_x][id_y] = Nmax(seg[2*id_x][id_y], seg[2*id_x + 1][id_y]);
        }
        else {
            int meio = (ini_y + fim_y) / 2;
            if (y <= meio)
                update_y(id_x, ini_x, fim_x, 2*id_y, ini_y, meio, x, y, new_val);
            else
                update_y(id_x, ini_x, fim_x, 2*id_y + 1, meio+1, fim_y, x, y, new_val);
            seg[id_x][id_y] = Nmax(seg[id_x][2*id_y], seg[id_x][2*id_y + 1]);
        }
    }

    void update_x(int id_x, int ini_x, int fim_x, int x, int y, int new_val) {
        if (ini_x != fim_x) {
            int meio = (ini_x + fim_x) / 2;
            if (x <= meio)
                update_x(2*id_x, ini_x, meio, x, y, new_val);
            else
                update_x(2*id_x + 1, meio+1, fim_x, x, y, new_val);
        }
        update_y(id_x, ini_x, fim_x, 1, 1, c, x, y, new_val);
    }
};

SegTree visited;

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

    visited.init();
    visited.build_x(1, 1, r);
    visited.update_x(1, 1, r, x1, y1, 0);

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
            aux = visited.query_x(1, 1, r, a1, b1, a2, b2);
            if (aux.val < 1) break;

            dist[aux.x][aux.y] = dist[u.first][u.second] + V[aux.x][aux.y];
            fila.push(make_pair(-dist[aux.x][aux.y], make_pair(aux.x, aux.y)));
            visited.update_x(1, 1, r, aux.x, aux.y, 0);
        }
    }
    return -1;
}

int main() {
    while (scanf("%d %d %d", &r, &c, &n) != EOF) {
        for (int i = 0; i < 505; i++)
            for (int j = 0; j < 505; j++) {
                V[i][j] = 0;
                R[i][j] = 0;
                C[i][j] = 0;
            }

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
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &x, &y);
            if (i > 1) printf(" ");
            if (i > 0) printf("%d", bfs(lx, ly, x, y));
            lx = x;
            ly = y;
        }
        printf("\n");
    }
    return 0;
}
