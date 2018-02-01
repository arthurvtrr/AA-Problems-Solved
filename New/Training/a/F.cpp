#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

int n, b[200200], c[200200];

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d", &b[i]);
    for (int i = 0; i < n; i++)
        scanf("%d", &c[i]);

    if (n == 1) {
        if (b[i] == c[i]) printf("%d\n", b[i]);
        else printf("-1\n");
    }
    else {
        vector < int > ans;

        int ini = 0, fim = b[0] + c[0] - b[1] - b[2];

    }

    return 0;
}
