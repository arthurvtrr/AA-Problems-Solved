#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <set>

using namespace std;

#define PI acos(-1)

struct point {
    double x, y;
    point() { x = y = 0; }
    point(double x, double y) : x(x), y(y) {}
} points[10];

point rotate(point p, double theta, point center) {
    double x = p.x - center.x;
    double y = p.y - center.y;

    double rad = theta * (PI / 180.0);
    return point(x * cos(rad) - y * sin(rad) + center.x, x * sin(rad) + y * cos(rad) + center.y);
}

int main() {
    for (int i = 0; i < 3; i++)
        scanf("%lf %lf", &points[i].x, &points[i].y);

    set < pair < int, int > > newp;

    for (int i = 0; i < 3; i++)
        for (int j = i+1; j < 3; j++) {
            point mid = point((points[i].x + points[j].x)/2, (points[i].y + points[j].y)/2);

            for (int k = 0; k < 3; k++)
                if (k != i && k != j) {
                    point p = rotate(points[k], 180.0, mid);
                    newp.insert(make_pair(round(p.x), round(p.y)));
                }
        }


    printf("%d\n", newp.size());
    for (set < pair < int, int > >::iterator it = newp.begin(); it != newp.end(); it++) {
        printf("%d %d\n", (*it).first, (*it).second);
    }

    return 0;
}
