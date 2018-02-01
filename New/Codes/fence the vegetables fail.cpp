#include <stdio.h>
#include <algorithm>
#include <map>

using namespace std;

#define N 110000

struct point {
    int x;
    int y;
    int type;
} points[2*N];

int p, v;

bool cmp(point a, point b) {

}

int main() {
    scanf("%d %d", &p, &v);
    for (int i = 0; i < p; i++) {
        scanf("%d %d", &points[i].x, points[i].y);
        points[i].type = 1;
    }
    for (int i = N; i < N+v; i++) {
        scanf("%d %d", &points[i].x, points[i].y);
        points[i].type = 2;
    }

    sort(points, points+n, cmp);
}
