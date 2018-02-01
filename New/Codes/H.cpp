#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

int t, ang, hour;
char s[10];

#define step 0.08333333333333333
#define EPS 1e-9

int main() {
    scanf("%d", &t);

    for (int tc = 1; tc <= t; tc++) {
        scanf("%d %s %d", &ang, s, &hour);

        ang *= 120;
        long double minutes = 216000.0, hours = 86400 + 3600.0*hour;

        if (strcmp(s, "til") == 0) {
            for (int i = 1; i < 50000; i++) {
                minutes -= 1.0;
                hours -= step;

                int dist = minutes - hours + 0.5 + EPS;
                if (dist % 43200 == ang) break;
            }
        }
        else {
            for (int i = 1; i < 50000; i++) {
                minutes += 1.0;
                hours += step;

                int dist = minutes - hours + 0.5 - EPS;
                if (dist % 43200 == ang) break;
            }
        }

        int h = ((int) (hours + EPS) % 43200) / 3600;
        int m = ((int) (minutes + EPS) % 43200) / 720;
        int s = (int) (minutes + EPS) % 60;
        printf("Case %d: %d:%02d:%02d\n", tc, h == 0? 12 : h, m, s);
    }

    return 0;
}
