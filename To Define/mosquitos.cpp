#include <stdio.h>
#include <math.h>

using namespace std;

int main() {
    int n, maxx = 0, minx = 200, maxy = 0, miny = 200, x, y;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x, &y);
        if (x > maxx) maxx = x;
        if (x < minx) minx = x;
        if (y > maxy) maxy = y;
        if (y < miny) miny = y;
    }
    int difx = maxx - minx, dify = maxy - miny;
    int sol = fmax(difx,dify) * fmax(difx,dify);
    printf("%d\n", sol);
    return 0;
}
