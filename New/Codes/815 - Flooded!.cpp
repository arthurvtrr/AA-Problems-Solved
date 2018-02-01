#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <map>

using namespace std;

#define EPS 1e-9

int n, m, lvl, volume;
map < int, int > region;

int main() {
    int cont = 1;
    while (1) {
        scanf("%d %d", &n, &m);
        if (n + m == 0) break;

        region.clear();

        for (int i = 0; i < n*m; i++) {
            scanf("%d", &lvl);
            region[lvl]++;
        }

        scanf("%d", &volume);

        double left = volume, water_lvl = 0.0, under_water = 0.0, total = n*m;

        for (map < int, int >::iterator it = region.begin(); it != region.end(); it++) {
            if (left < EPS) break;

            under_water += it->second;

            map < int, int >::iterator next = it;
            next++;

            if (next != region.end()) {
                double a = it->first, b = next->first;

                if (a + left / (under_water * 100) < b - EPS) {
                    water_lvl = a + left / (under_water * 100);
                    left = 0.0;
                }
                else {
                    water_lvl = b;
                    left -= (b-a) * under_water * 100;
                }
            }
            else
                water_lvl = it->first + left / (under_water * 100);
        }

        printf("Region %d\n", cont++);
        printf("Water level is %.2f meters.\n", water_lvl);
        printf("%.2f percent of the region is under water.\n\n", under_water / total * 100);
    }
    return 0;
}
