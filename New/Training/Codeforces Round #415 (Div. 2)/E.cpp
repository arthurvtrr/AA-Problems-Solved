#include <bits/stdc++.h>

using namespace std;

#define MOD 1000000007
#define ll long long

int q;

struct query {
    ll x1, y1, x2, y2, k;
} queries[10010];

int main() {
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        scanf("%lld %lld", &queries[i].x1, &queries[i].y1);
        scanf("%lld %lld", &queries[i].x2, &queries[i].y2);
        scanf("%lld", &queries[i].k);
    }



    return 0;
}
