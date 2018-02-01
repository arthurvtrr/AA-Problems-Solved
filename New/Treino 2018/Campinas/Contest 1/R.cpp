#include <bits/stdc++.h>

using namespace std;

#define ll long long

ll a, b, c;

int main() {
    scanf("%lld %lld %lld", &a, &b, &c);

    if (a == 0 && b == 0 && c == 0) printf("-1\n");
    else if (a == 0 && b == 0) printf("0\n");
    else if (a == 0 && c == 0) printf("1\n0\n");
    else if (a == 0) {
        printf("1\n");
        long double ans = -c;
        ans /= b;
        printf("%Lf\n", ans);
    }
    else {
        ll delta = b*b - 4*a*c;
        if (delta < 0) printf("0\n");
        else if (delta == 0) {
            printf("1\n");
            long double ans = -b;
            ans /= 2*a;
            printf("%Lf\n", ans);
        }
        else {
            printf("2\n");
            vector < long double > aux;
            long double ans = -b;
            ans -= sqrtl(delta);
            ans /= 2*a;
            aux.push_back(ans);
            ans = -b;
            ans += sqrtl(delta);
            ans /= 2*a;
            aux.push_back(ans);
            sort(aux.begin(), aux.end());
            printf("%Lf\n%Lf\n", aux[0], aux[1]);
        }
    }
    return 0;
}
