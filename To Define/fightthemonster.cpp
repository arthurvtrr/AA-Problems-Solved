#include <stdio.h>
#include <algorithm>

using namespace std;

int main() {
    int hpy, atky, defy;
    scanf("%d %d %d", &hpy, &atky, &defy);
    int hpm, atkm, defm;
    scanf("%d %d %d", &hpm, &atkm, &defm);
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);

    int sol = 1000000000;
    for (int i = 0; i < 200; i++)
        for (int j = 0; j < 100; j++) {
            int ay = atky + i, dy = defy + j;
            if (ay <= defm) continue;
            int hp = (atkm <= dy? 0 : (ceil(1.0*hpm / (ay - defm)) * (atkm - dy) + 1));
            if (a*max(0, hp - hpy) + b*i + c*j < sol)
                sol = a*max(0, hp - hpy) + b*i + c*j;
        }

    printf("%d\n", sol);
    return 0;
}
