#include <stdio.h>
#include <algorithm>

using namespace std;

#define ll long long

ll n, b;

ll b_search(ll ini, ll fim) {
    ll e = ini, d = fim;
    while (e <= d) {
        ll x = (e + d) / 2;
        ll aux = (x*n - x*x) * 4;

        if (aux <= 0) d = x-1;
        else if (aux == b) return x;
        else if (aux < b) e = x+1;
        else d = x-1;
    }
    return max((ll) 0, d);
}

int main() {
    while (scanf("%lld %lld", &n, &b) != EOF) {
        if (n*n == b && n % 2 == 1) {
            printf("%d %d\n", n/2+1, n/2+1);
            continue;
        }

        int x = 1, y = 0;
        ll c = b_search(0, n);
        x += c;
        y += c;

        b -= (c*n - c*c) * 4;

        if (b) {
            if (n - c*2 > 0 && b >= n - c*2) {y += n - c*2; b -= n - c*2;}
            else {y += b; b = 0;}
            if (n - c*2 - 1 > 0 && b >= n - c*2 - 1) {x += n - c*2 - 1; b -= n - c*2 - 1;}
            else {x += b; b = 0;}
            if (n - c*2 - 1 > 0 && b >= n - c*2 - 1) {y -= n - c*2 - 1; b -= n - c*2 - 1;}
            else {y -= b; b = 0;}
            if (n - c*2 - 2 > 0 && b >= n - c*2 - 2) {x -= n - c*2 - 2; b -= n - c*2 - 2;}
            else {x -= b; b = 0;}
        }

        printf("%d %d\n", x, y);
    }
    return 0;
}
