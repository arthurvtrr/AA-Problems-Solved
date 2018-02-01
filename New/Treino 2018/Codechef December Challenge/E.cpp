#include <bits/stdc++.h>

using namespace std;

int t, x, y, z, a, b, c;

int f(int quant) {
    int xx = x, yy = y, zz = z;

    int ret = quant*c;
    xx -= quant; yy -= quant; zz -= quant;

    if (2*a <= b) ret += (xx + yy + zz) * a;
    else {
        int dif = yy - xx;
        ret += dif * b;
        yy -= dif; zz -= dif;
        if (zz > 2*xx) {
            ret += 2*xx*b;
            ret += (zz-2*xx)*a;
        }
        else {
            int lft = zz - xx;
            ret += 2*lft*b;
            xx -= lft;
            ret += xx/2*3*b;
            if (xx % 2) ret += a+b;
        }
    }

    return ret;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d %d %d %d %d", &x, &y, &z, &a, &b, &c);
        if (x > y) swap(x, y);
        if (y > z) swap(y, z);
        if (x > y) swap(x, y);

        int ans = min(f(x), f(x-1));

        for (int i = 0; i <= min(x, 100); i++)
            ans = min(ans, f(i));

        if (x > 100) {
            int lo = -1, hi = x;
            while (hi - lo > 1) {
                int mid = (hi + lo)>>1;
                if (f(mid) < f(min(x, mid + 2)))
                     hi = mid;
                else
                     lo = mid;
            }
            ans = min(ans, f(lo+1));
        }
        printf("%d\n", ans);
    }
    return 0;
}
