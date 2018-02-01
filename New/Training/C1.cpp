#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

int n, m;

#define pii pair < int, int >

pii subs[100100];

int main() {
    scanf("%d %d", &n, &m);

    int mini = 10000000;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &subs[i].first, &subs[i].second);
        mini = min(mini, subs[i].second - subs[i].first + 1);
    }

    int cont = 0;
    printf("%d\n", mini);

    for (int i = 0; i < n; i++) {
        if (i > 0) printf(" ");
        printf("%d", cont);
        cont++;
        cont %= mini;
    }
    printf("\n");

    return 0;
}

