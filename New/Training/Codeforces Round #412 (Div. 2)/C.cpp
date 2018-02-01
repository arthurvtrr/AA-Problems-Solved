#include <bits/stdc++.h>

using namespace std;

#define ll long long

int t;
ll ix, iy, p, q;


int main() {
    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        scanf("%lld %lld %lld %lld", &ix, &iy, &p, &q);
        ll ans = 0;

        if (ix == 0 && p == 0) printf("0\n");
        else if (p == 0) printf("-1\n");
        else if (ix == iy && p == q) printf("0\n");
        else if (p == q) printf("-1\n");
        else {
            int oper = 10;
            while (ix * q != iy * p && oper--) {
                if (ix * q < iy * p) {
                    ll bef = iy * p - ix * q, af = (iy+1) * p - (ix+1) * q;

                    ix += bef / (bef - af);
                    iy += bef / (bef - af);
                    ans += bef / (bef - af);
                }
                else {
                    ll dec = (ix * q - iy * p) / p;
                    iy += dec;
                    ans += dec;
                }
                printf("%lld %lld\n", ix, iy);
            }

            if (ix * q != iy * p) printf("-1\n");
            else printf("%lld\n", ans);
        }
    }

    return 0;
}
