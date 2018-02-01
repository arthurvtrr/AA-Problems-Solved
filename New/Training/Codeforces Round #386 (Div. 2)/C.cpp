#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

int s, x1, x2, t1, t2, p, d;

int main() {
    scanf("%d %d %d", &s, &x1, &x2);
    scanf("%d %d", &t1, &t2);
    scanf("%d %d", &p, &d);

    int walking = abs(x1-x2) * t2;

    int tram, dist = 0, pos = p;
    bool found = (pos == x1);

    while (pos != x2 || !found) {
        pos += d;
        if (pos == s || pos == 0) d = -d;
        if (pos == x1) found = true;
        dist++;
    }
    tram = dist * t1;

    int sol = min(walking, tram);
    printf("%d\n", sol);
    return 0;
}


