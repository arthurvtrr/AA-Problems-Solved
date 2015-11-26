#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

int main() {

    int t, d, m, p[1100];
    vector < int > maxim;
    bool f;

    scanf("%d", &t);

    for (int i = 0; i < t; i++) {
        memset(p, 0, 4400);
        m = 0;
        f = false;
        maxim.clear();

        scanf("%d", &d);
        int x;
        for (int j = 0; j < d; j++) {
            scanf("%d", &x);
            p[x]++;
        }

        for (int k = 1005; k >= 0; k--) {
            if (p[k] > 0) {
                maxim.push_back(k + m);
                if (p[k] < k/2) {
                    int a = k / 2;
                    p[a] += p[k];
                    p[k - a] += p[k];
                    m += p[k];
                    p[k] = 0;
                }
                else {
                    m += k;
                    maxim.push_back(m);
                    break;
                }
                maxim.push_back(k + m);
            }
        }

        int mi = 9;
        for (int n : maxim) {
            if (n < mi)
                mi = n;
        }
        printf("Case #%d: %d\n", i+1, mi);
    }

    return 0;
}
