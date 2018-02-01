#include <bits/stdc++.h>

using namespace std;

long long point[5][2];

long long dist(int a, int b) {
    return (point[a][0] - point[b][0])*(point[a][0] - point[b][0]) + (point[a][1] - point[b][1])*(point[a][1] - point[b][1]);
}

long long cross(int a, int b) {
    return point[a][0] * point[b][1] - point[a][1] * point[b][0];
}

bool collinear(int a, int b, int c) {
    return cross(3, 4) == 0;
}

int main() {
    for (int i = 0; i < 3; i++)
        scanf("%lld %lld", &point[i][0], &point[i][1]);

    point[3][0] = point[1][0] - point[0][0];
    point[3][1] = point[1][1] - point[0][1];
    point[4][0] = point[2][0] - point[0][0];
    point[4][1] = point[2][1] - point[0][1];

    if (dist(0, 1) == dist(1, 2) && !collinear(0, 1, 2)) printf("Yes\n");
    else printf("No\n");

    return 0;
}

