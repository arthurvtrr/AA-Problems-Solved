#include <bits/stdc++.h>

using namespace std;

#define PI acos(-1)
#define EPS 1e-9

struct point {
    int d[5];
    point() {
        d[0] = d[1] = d[2] = d[3] = d[4] = 0;
    }
    point(int a1, int b1, int c1, int d1, int e1) {
        d[0] = a1; d[1] = b1; d[2] = c1; d[3] = d1; d[4] = e1;
    }
} p[1010];

int n;

double angle(point a, point b, point c) {
    point ab = point(b.d[0] - a.d[0], b.d[1] - a.d[1], b.d[2] - a.d[2], b.d[3] - a.d[3], b.d[4] - a.d[4]);
    point ac = point(c.d[0] - a.d[0], c.d[1] - a.d[1], c.d[2] - a.d[2], c.d[3] - a.d[3], c.d[4] - a.d[4]);

    double num = ab.d[0]*ac.d[0] + ab.d[1]*ac.d[1] + ab.d[2]*ac.d[2] + ab.d[3]*ac.d[3] + ab.d[4]*ac.d[4];
    double denx = sqrt(ab.d[0]*ab.d[0] + ab.d[1]*ab.d[1] + ab.d[2]*ab.d[2] + ab.d[3]*ab.d[3] + ab.d[4]*ab.d[4]);
    double deny = sqrt(ac.d[0]*ac.d[0] + ac.d[1]*ac.d[1] + ac.d[2]*ac.d[2] + ac.d[3]*ac.d[3] + ac.d[4]*ac.d[4]);
    return acos(num / denx / deny) * 180.0 / PI;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < 5; j++)
            scanf("%d", &p[i].d[j]);

    vector < int > good;
    for (int i = 0; i < n; i++) {
        bool valid = true;
        for (int j = 0; j < n; j++) {
            if (j == i) continue;
            for (int k = 0; k < n; k++) {
                if (k == i || k == j) continue;
                if (angle(p[i], p[j], p[k]) + EPS < 90.0) {
                    valid = false;
                    break;
                }
            }
        }
        if (valid) good.push_back(i+1);
    }

    printf("%d\n", good.size());
    for (int i = 0; i < good.size(); i++)
        printf("%d\n", good[i]);

    return 0;
}
