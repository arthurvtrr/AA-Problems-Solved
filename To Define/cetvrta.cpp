#include <stdio.h>
#include <algorithm>

using namespace std;

struct point {
    int x;
    int y;
} points[5];

bool cmp1(point a, point b) {
    return a.x < b.x;
}

bool cmp2(point a, point b) {
    return a.y < b.y;
}

int main() {
    for (int i = 0; i < 3; i++)
        scanf("%d %d", &points[i].x, &points[i].y);

    int a, b;

    sort(points, points+3, cmp1);
    if (points[0].x != points[1].x) a = points[0].x;
    else a = points[2].x;

    sort(points, points+3, cmp2);
    if (points[0].y != points[1].y) b = points[0].y;
    else b = points[2].y;

    printf("%d %d\n", a, b);

    return 0;
}
