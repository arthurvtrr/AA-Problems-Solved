#include <bits/stdc++.h>

using namespace std;

struct tree {
    int x;
    int h;
    int dist1;
    int dist2;
} trees[110000];

int main() {
    int n, cutted = 1;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
        scanf("%d %d", &trees[i].x, &trees[i].h);

    for (int i = 2; i < n; i++) {
        trees[i].dist1 = trees[i].x - trees[i-1].x;
        trees[i].dist2 = trees[i+1].x - trees[i].x;
    }

    for (int i = 2; i < n; i++) {
        if (trees[i].dist1 > trees[i].h) {
            cutted++;
        }
        else if (trees[i].dist2 > trees[i].h) {
            cutted++;
            trees[i+1].dist1 -= trees[i].h;
        }
    }

    if (n > 1) cutted++;
    printf("%d\n", cutted);

    return 0;
}
