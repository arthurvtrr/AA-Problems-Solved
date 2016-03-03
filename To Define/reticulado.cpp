#include <stdio.h>
#include <map>

using namespace std;

int main() {
    int c, n;
    scanf("%d", &c);
    for (int t = 0; t < c; t++) {
        scanf("%d", &n);
        map < double, int > coef;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) {
                double ind = 1.0 * i / j;
                coef[ind]++;
            }
        printf("%d %d %d\n", t+1, n, coef.size() + 2);
    }
    return 0;
}
