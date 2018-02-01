#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define EPS 1e-9

int n, r;
ll nums[1010];

struct point {
    double x, y;
    point(double x, double y) : x(x), y(y) {}
    point operator - (const point &p) const { return point(x-p.x, y-p.y); }
};

double dot(point p, point q) { return p.x*q.x+p.y*q.y; }
double dist2(point p, point q) { return dot(p-q, p-q); }

bool CircleCircleIntersection(point a, point b) {
    double d = sqrt(dist2(a, b));
    if (d <= 2*r) return true;
    return false;
}

int main() {
    scanf("%d %d", &n, &r);
    for (int i = 0; i < n; i++)
        scanf("%lld", &nums[i]);

    vector < double > center;
    center.push_back(r);

    for (int i = 1; i < n; i++) {
        double maxc = r;

        for (int j = 0; j < i; j++) {
            if (abs(nums[i] - nums[j]) < 2*r) {
                double ini = 2000000.0, fim = center[j];
                while (fabs(ini - fim) > EPS) {
                    double meio = (ini + fim) / 2;
                    if (CircleCircleIntersection(point(nums[j], center[j]), point(nums[i], meio))) fim = meio;
                    else ini = meio;
                }
                maxc = max(maxc, ini);
            }
            else if (abs(nums[i] - nums[j]) == 2*r) {
                maxc = max(maxc, center[j]);
            }
        }
        center.push_back(maxc);
    }

    for (int i = 0; i < n; i++) {
        if (i) printf(" ");
        printf("%.10f", center[i]);
    }
    printf("\n");

    return 0;
}
