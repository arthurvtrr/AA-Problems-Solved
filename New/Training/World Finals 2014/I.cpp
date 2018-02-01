#include <bits/stdc++.h>

using namespace std;

int n, d;

struct point {
    int x, y;
    point() { x = y = 0; }
    point(int x, int y): x(x), y(y) {}
} points[110];

int dist(point a, point b) {
    return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

int cross(point a, point b) {
    return a.x * b.y - a.y * b.x;
}

bool ccw(point p, point q, point r) {
    return cross(point(q.x - p.x, q.y - p.y), point(r.x - p.x, r.y - p.y)) > 0;
}

#define N 110

vector < int > graph[N];
bool visited[N];
int matchs[N];

bool match_vertex(int u) {
    for (int v : graph[u])
        if (!visited[v]) {
            visited[v] = true;
            if (matchs[v] < 0 || match_vertex(matchs[v])) {
                matchs[v] = u;
                return true;
            }
        }
    return false;
}

int max_match() {
    memset(matchs, -1, sizeof(matchs));
    int result = 0;
    for (int u = 0; u < n; u++) {
        memset(visited, 0, sizeof(visited));
        if (match_vertex(u)) result++;
    }
    return result;
}

bool lft[N], valid[N], cover[N];
vector < int > cgraph[N];

void dfs(int u) {
    visited[u] = true;
    for (int v : cgraph[u])
        if (!visited[v]) {
            if (matchs[u] == v && !lft[u]) dfs(v);
            else if (matchs[u] != v && lft[u]) dfs(v);
        }
}

int main() {
    scanf("%d %d", &n, &d);
    for (int i = 0; i < n; i++)
        scanf("%d %d", &points[i].x, &points[i].y);

    vector < int > ans = {1}, aux, best;

    for (int i = 0; i < n; i++)
        for (int j = i+1; j < n; j++) {
            int x = dist(points[i], points[j]);
            if (x > d*d) continue;

            for (int a = 0; a < N; a++) {
                graph[a].clear();
                cgraph[a].clear();
                lft[a] = valid[a] = cover[a] = false;
            }
            aux.clear(); best.clear();

            for (int a = 0; a < n; a++)
                if (dist(points[a], points[i]) <= x && dist(points[a], points[j]) <= x)
                    aux.push_back(a);

            for (int a = 0; a < aux.size(); a++) {
                valid[aux[a]] = true;
                for (int b = 0; b < aux.size(); b++)
                    if (dist(points[aux[a]], points[aux[b]]) > x) {
                        valid[aux[a]] = false;
                        if (a >= b) continue;

                        if (ccw(points[i], points[j], points[aux[a]])) {
                            graph[aux[a]].push_back(aux[b]);
                            lft[aux[a]] = true;
                        }
                        else {
                            graph[aux[b]].push_back(aux[a]);
                            lft[aux[b]] = true;
                        }

                        cgraph[aux[a]].push_back(aux[b]);
                        cgraph[aux[b]].push_back(aux[a]);
                    }
            }

            max_match();
            for (int a = 0; a < n; a++)
                if (matchs[a] != -1)
                    matchs[matchs[a]] = a;

            memset(visited, 0, sizeof(visited));

            for (int a = 0; a < aux.size(); a++)
                if (matchs[aux[a]] == -1 && lft[aux[a]])
                    dfs(aux[a]);

            for (int a = 0; a < aux.size(); a++) {
                if (lft[aux[a]] && !visited[aux[a]]) cover[aux[a]] = true;
                else if (!lft[aux[a]] && visited[aux[a]]) cover[aux[a]] = true;
            }

            for (int a = 0; a < aux.size(); a++)
                if (!cover[aux[a]])
                    best.push_back(aux[a]+1);

            if (best.size() > ans.size()) ans = best;
        }

    printf("%d\n", ans.size());
    for (int i = 0; i < ans.size(); i++) {
        if (i) printf(" ");
        printf("%d", ans[i]);
    }
    printf("\n");

    return 0;
}
