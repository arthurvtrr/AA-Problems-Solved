#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

struct point {
    int x;
    int y;
    int ind;
};

bool comp1(point x, point y) {
    return x.y < y.y;
}

bool comp2(point x, point y) {
    return x.y > y.y;
}

int main() {
    vector < point > regions[1100];
    int n, x, y;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x, &y);
        regions[x / 1000].push_back((point) {x, y, i+1});
    }

    for (int i = 0; i < 1100; i++) {
        if (i % 2 == 0) sort(regions[i].begin(), regions[i].end(), comp1);
        else sort(regions[i].begin(), regions[i].end(), comp2);
    }
    for (int i = 0; i < 1100; i++) {
        for (int j = 0; j < regions[i].size(); j++) {
            if (i != 0 || j != 0) printf(" ");
            printf("%d", regions[i][j].ind);
        }
    }
    printf("\n");
    return 0;
}
