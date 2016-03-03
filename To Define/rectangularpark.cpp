#include <stdio.h>
#include <algorithm>

using namespace std;

struct coord {
    int x;
    int y;
} coords[3300];

bool comp(coord a, coord b) {
    return a.x < b.x;
}

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; i++)
            scanf("%d %d", &coords[i].x, &coords[i].y);

        sort(coords, coords+n, comp);

        int sol = 0;
        for (int i = 0; i < n; i++) {
            int max_y = -1000000000, min_y = 1000000000;
            for (int j = i+1; j < n; j++) {
                if (coords[j].y < coords[i].y && coords[j].y > max_y) {
                    sol++;
                    max_y = coords[j].y;
                }
                else if (coords[j].y > coords[i].y && coords[j].y < min_y) {
                    sol++;
                    min_y = coords[j].y;
                }
            }
        }

        printf("%d\n", sol);
    }
    return 0;
}
