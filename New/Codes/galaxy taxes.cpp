#include <stdio.h>
#include <algorithm>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;

int n, m;

double dist[1100];
bool visited[1100];

#define INF 2000000000
#define idd tuple < int, double, double >
#define EPS 1e-9

vector < idd > graph[1100];

double bfs(double t) {
    for (int i = 0; i < 1100; i++) {
        visited[i] = false;
        dist[i] = INF;
    }

    priority_queue < pair < double, int > > fila;

    dist[1] = 0.0;
    fila.push(make_pair(0.0, 1));

    while (!fila.empty()) {
        int u = fila.top().second;
        fila.pop();
        visited[u] = true;

        for (idd v : graph[u]) {
            if (!visited[get<0>(v)] && dist[get<0>(v)] > dist[u] + (get<1>(v) * t + get<2>(v)) - EPS) {
                dist[get<0>(v)] = dist[u] + (get<1>(v) * t + get<2>(v));
                fila.push(make_pair(-dist[get<0>(v)], get<0>(v)));
            }
        }
    }

    return dist[n];
}

int main() {
    while (scanf("%d %d", &n, &m) != EOF) {
        for (int i = 0; i < 1100; i++)
            graph[i].clear();

        int x, y;
        double a, b;

        for (int i = 0; i < m; i++) {
            scanf("%d %d %lf %lf", &x, &y, &a, &b);
            graph[x].push_back(make_tuple(y, a, b));
            graph[y].push_back(make_tuple(x, a, b));
        }

        double left = 0.0, right = 24.0 * 60.0;
        int iterations_left = 100;

        while (iterations_left--) {
            double leftThird = (2*left + right)/3;
            double rightThird = (left + 2*right)/3;

            if (bfs(leftThird) < bfs(rightThird) + EPS)
                left = leftThird;
            else
                right = rightThird;
        }

        printf("%.5f\n", bfs(left));
    }
    return 0;
}
