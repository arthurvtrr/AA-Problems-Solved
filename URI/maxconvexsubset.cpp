#include <stdio.h>
#include <algorithm>

using namespace std;

struct point {
    int x;
    int y;
} points[55];

struct vetor {
    int x;
    int y;
};

int n;
point origem;
vector < point > aux;

bool ccw(point o, point a, point b) {
    int x1 = a.x - o.x, y1 = a.y - o.y;
    int x2 = b.x - o.x, y2 = b.y - o.y;
    return x1 * y2 - x2 * y1 >= 0;
}

bool cmp1(point a, point b) {
    return a.x < b.x;
}

bool cmp2(point a, point b) {
    return ccw(origem, a, b);
}

int solve() {

}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d %d", &points[i].x, &points[i].y);

    sort(points, points+n, cmp1);

    int ans = 0;
    for (int i = 0; i < n; i++) {
        aux.clear();
        origem = points[i];
        for (int j = i; j < n; j++)
            aux.push_back(points[j]);
        sort(aux.begin(), aux.end(), cmp2);
        ans = max(ans, solve());
    }

    printf("%d\n", ans);

    return 0;
}
