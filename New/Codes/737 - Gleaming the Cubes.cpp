#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

int n;

struct cube {
    int x, y, z;
    int d_x, d_y, d_z;

    cube() {
        x = y = z = d_x = d_y = d_z = 0;
    }

} cubes[1100];

bool intersect(cube a, cube b) {
    if (a.x <= b.x && a.x + a.d_x <= b.x) return false;
    if (a.x >= b.x && b.x + b.d_x <= a.x) return false;
    if (a.y <= b.y && a.y + a.d_y <= b.y) return false;
    if (a.y >= b.y && b.y + b.d_y <= a.y) return false;
    if (a.z <= b.z && a.z + a.d_z <= b.z) return false;
    if (a.z >= b.z && b.z + b.d_z <= a.z) return false;
    return true;
}

int main() {
    while (scanf("%d", &n), n) {
        for (int i = 0; i < n; i++) {
            scanf("%d %d %d %d", &cubes[i].x, &cubes[i].y, &cubes[i].z, &cubes[i].d_x);
            cubes[i].d_y = cubes[i].d_z = cubes[i].d_x;
        }

        cube intersec = cubes[0];

        for (int j = 1; j < n; j++)
            if (intersect(intersec, cubes[j])) {
                if (intersec.x <= cubes[j].x) {
                    intersec.d_x = min(cubes[j].d_x, intersec.x + intersec.d_x - cubes[j].x);
                    intersec.x = cubes[j].x;
                }
                else
                    intersec.d_x = min(intersec.d_x, cubes[j].x + cubes[j].d_x - intersec.x);

                if (intersec.y <= cubes[j].y) {
                    intersec.d_y = min(cubes[j].d_y, intersec.y + intersec.d_y - cubes[j].y);
                    intersec.y = cubes[j].y;
                }
                else
                    intersec.d_y = min(intersec.d_y, cubes[j].y + cubes[j].d_y - intersec.y);

                if (intersec.z <= cubes[j].z) {
                    intersec.d_z = min(cubes[j].d_z, intersec.z + intersec.d_z - cubes[j].z);
                    intersec.z = cubes[j].z;
                }
                else
                    intersec.d_z = min(intersec.d_z, cubes[j].z + cubes[j].d_z - intersec.z);
            }
            else intersec = cube();

        printf("%d\n", intersec.d_x * intersec.d_y * intersec.d_z);
    }
    return 0;
}
