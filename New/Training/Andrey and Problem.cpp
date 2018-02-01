#include <bits/stdc++.h>

using namespace std;

int n;
double p[110];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%lf", &p[i]);

    sort(p, p+n);

    double ans = p[n-1];
    for (int i = 1; i < n; i++) {
        double prob = p[i], inv = 1 - p[i];
        for (int j = i-1; j >= 0; j--) {
            double np = prob * (1 - p[j]) + p[j] * inv;
            if (np > prob) {
                prob = np;
                inv *= 1 - p[j];
            }
        }
        ans = max(ans, prob);
    }

    printf("%.12f\n", ans);
    return 0;
}
