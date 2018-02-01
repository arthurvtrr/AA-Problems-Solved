#include <stdio.h>
#include <algorithm>

using namespace std;

#define EPS 1e-9

int n;
double x, y;

int main() {
    while (scanf("%d", &n), n) {
        double maxi = -1.0;
        int ind = -1;

        for (int i = 0; i < n; i++) {
            scanf("%lf %lf", &x, &y);
            if (maxi < min(x, y / 4) - EPS) {
                maxi = min(x, y / 4);
                ind = i+1;
            }
            if (maxi < min(y, x / 4) - EPS) {
                maxi = min(y, x / 4);
                ind = i+1;
            }
            if (maxi < min(x / 2, y / 2) - EPS) {
                maxi = min(x / 2, y / 2);
                ind = i+1;
            }
        }

        printf("%d\n", ind);
    }
    return 0;
}
