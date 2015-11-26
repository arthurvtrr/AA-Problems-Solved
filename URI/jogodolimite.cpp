#include <stdio.h>
#include <algorithm>

using namespace std;

int main() {
    int n, t, l;
    scanf("%d %d %d", &n, &t, &l);
    int pont[] = {0, 0}, x;
    for (int i = 0; i < n-1; i++) {
        scanf("%d", &x);
        if (abs(t-x) <= l) {
            pont[i%2] += abs(t-x);
            t = x;
        }
    }
    printf("%d %d\n", pont[0], pont[1]);
    return 0;
}
