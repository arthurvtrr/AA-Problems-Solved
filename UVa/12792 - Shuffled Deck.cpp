#include <stdio.h>
#include <algorithm>

using namespace std;

int main() {
    int p;
    while (scanf("%d", &p) != EOF) {
        int x = 2, cont = 1;
        while (x-1 != 0) {
            x *= 2;
            x %= p+1;
            cont++;
        }
        printf("%d\n", cont);
    }
    return 0;
}
