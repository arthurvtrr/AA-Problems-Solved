#include <bits/stdc++.h>

using namespace std;

#define EPS 1e-7

int n, l, dist[100100];
double a, d, v[100100], w[100100];

int main() {
    while (1) {
        scanf("%d %d %lf %lf", &n, &l, &a, &d);
        if (n == -1) break;

        for (int i = 0; i < n; i++)
            scanf("%d %lf %lf", &dist[i], &v[i], &w[i]);

        bool possible = true;

        for (int i = n-2; i >= 0; i--) {
            int d1 = dist[i+1] - dist[i];

            double minv = v[i+1]*v[i+1] - 2*a*d1 < EPS? 0.0 : sqrt(v[i+1]*v[i+1] - 2*a*d1);
            double maxv = sqrt(w[i+1]*w[i+1] + 2*d*d1);

            if (minv > w[i] || maxv < v[i]) possible = false;
            else {
                w[i] = min(w[i], maxv);
                v[i] = max(v[i], minv);
            }
        }

        double ans = 0.0, atualv = 0.0;
        for (int i = 0; i < n; i++) {
            int d1 = dist[i] - (i == 0? 0 : dist[i-1]);

            if (atualv <= w[i]) {
                double nv = sqrt(atualv*atualv + 2*a*d1);

                if (nv < v[i]) possible = false;
                else if (nv <= w[i]) {
                    ans += (nv - atualv) / a;
                    atualv = nv;
                }
                else {
                    double ini = w[i], fim = 50000.0;
                    while (fabs(ini - fim) > EPS) {
                        double mid = (ini + fim) / 2;

                        double da = (mid*mid - atualv*atualv) / (2*a);
                        double db = (w[i]*w[i] - mid*mid) / (-2*d);
                        if (da + db <= d1) ini = mid;
                        else fim = mid;
                    }

                    ans += (ini - atualv) / a;
                    double dl = d1 - (ini*ini - atualv*atualv) / (2*a);
                    ans += (w[i] - ini) / (-d);
                    atualv = w[i];
                }
            }
            else {
                double ini = atualv, fim = 50000.0;
                while (fabs(ini - fim) > EPS) {
                    double mid = (ini + fim) / 2;

                    double da = (mid*mid - atualv*atualv) / (2*a);
                    double db = (w[i]*w[i] - mid*mid) / (-2*d);
                    if (da + db <= d1) ini = mid;
                    else fim = mid;
                }

                ans += (ini - atualv) / a;
                double dl = d1 - (ini*ini - atualv*atualv) / (2*a);
                ans += (w[i] - ini) / (-d);
                atualv = w[i];
            }
        }

        int d1 = l - dist[n-1];
        ans += (sqrt(atualv*atualv + 2*a*d1) - atualv) / a;

        if (possible) printf("%.2f\n", ans);
        else printf("*\n");
    }
    return 0;
}
