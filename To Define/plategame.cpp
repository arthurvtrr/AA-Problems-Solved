#include <stdio.h>
#include <algorithm>

using namespace std;

int main() {
    int a, b, r;
    scanf("%d %d %d", &a, &b, &r);

    if (r*2 > min(a,b)) printf("Second\n");
    else printf("First\n");

    return 0;
}
