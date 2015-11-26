#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

struct point {
    int x;
    int y;
} points[1100];

int main() {
    int n, sol = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d %d", &points[i].x, &points[i].y);

    int aux = 1;
    vector < int > areas;
    for (int i = 0; i < 102; i++) {
        areas.clear();
        for (int j = 0; j < n; j++) {

        }
    }
    return 0;
}
