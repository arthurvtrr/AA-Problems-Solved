#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <map>
#include <vector>

using namespace std;

#define pii pair <int, int>
#define MOD 1000000007

int n, m, x, y;
vector < int > gyms[1000100];

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        for (int j = 0; j < x; j++) {
            scanf("%d", &y);
            gyms[y].push_back(i);
        }
    }

    sort(gyms+1, gyms+m+1);

    long long sol = 1, siz = 1;
    for (int i = 1; i < m; i++) {
        if (gyms[i] == gyms[i+1]) siz++;
        else siz = 1;
        sol *= siz;
        sol %= MOD;
    }
    printf("%lld\n", sol);

    return 0;
}
