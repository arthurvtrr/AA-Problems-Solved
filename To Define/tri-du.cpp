#include <stdio.h>
#include <algorithm>

using namespace std;

int main() {
    int a, b;
    while (scanf("%d %d", &a, &b) != EOF) {
    printf("%d\n", max(a,b));
    }
    return 0;
}
