#include <bits/stdc++.h>

using namespace std;

#define INF 1e100
#define EPS 1e-9
#define N 220
#define M 4040

int n, m, x, y, z;
double v, a[M][N], b[M], c[N];

void pivot(int l, int e) {
    b[l] /= a[l][e];
    for (int i = 1; i <= n; i++)
    	if (i != e)
    		a[l][i] /= a[l][e];

    for (int i = 1; i <= m; i++)
        if (i != l && fabs(a[i][e]) > EPS) {
            b[i] -= a[i][e] * b[l];
            for (int j = 1; j <= n; j++)
            	if (j != e)
            		a[i][j] -= a[i][e] * a[l][j];

            a[i][e] = -a[i][e] * a[l][e];
        }

    v += c[e] * b[l];
    for(int i = 1; i <= n; i++)
    	if (i != e)
    		c[i] -= c[e] * a[l][i];

    c[e] = -c[e] * a[l][e];
}

double simplex() {
    int l, e;
    while (1) {
        for (e = 1; e <= n; e++)
        	if (c[e] > EPS)
        		break;

        if (e == n+1) return v;

        double tmp = INF;
        for (int i = 1; i <= m; i++)
            if (a[i][e] > EPS && b[i] / a[i][e] < tmp)
            	tmp = b[i] / a[i][e], l = i;

        if(tmp == INF) return INF;
        pivot(l, e);
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%lf", &c[i]);
    for (int i = 1; i <= m; i++) {
        scanf("%d %d %d", &x, &y, &z);
        for (int j = x; j <= y; j++)
            a[i][j] = 1;
        b[i] = z;
    }
    printf("%lld\n", (long long)(simplex() + 0.5));

    return 0;
}
