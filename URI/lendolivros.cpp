#include <stdio.h>
#include <math.h>

using namespace std;

int main() {
    int q, d, p;
    while(scanf("%d", &q) && q != 0) {
        scanf("%d %d", &d, &p);

        for (int i = 0; i < 10000; i++) {
            if (q*i == p*(i-d)) {
                printf("%d paginas\n", q*i);
                break;
            }
        }
    }
    return 0;
}
