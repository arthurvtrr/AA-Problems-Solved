#include <stdio.h>
#include <algorithm>

using namespace std;

struct alien {
    int x;
    int y;
    int d;
} aliens[330];

bool cmp(alien x, alien y) {
    return x.d > y.d;
}

int main() {
    int t, n;
    scanf("%d", &t);
    for (int tc = 0; tc < t; tc++) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d %d %d", &aliens[i].x, &aliens[i].y, &aliens[i].d);

        sort(aliens, aliens+n, cmp);

        int sol = 0;
        for (int i = 0; i < n; i++) {
            vector < int > used;
            if (aliens[i].x == -1) continue;
            used.push_back(i);
            int a = aliens[i].x, b = aliens[i].y;
            for (int j = i+1; j < n; j++) {
                if (aliens[j].x == -1) continue;
                if (aliens[j].x <= a && aliens[j].y >= b)
                    used.push_back(j);
                else if (aliens[j].x < a && aliens[j].y >= a) {
                    used.push_back(j);
                    b = aliens[j].y;
                }
                else if (aliens[j].x <= b && aliens[j].y > b) {
                    used.push_back(j);
                    a = aliens[j].x;
                }
                else if (aliens[j].x > a && aliens[j].y < b) {
                    used.push_back(j);
                    a = aliens[j].x;
                    b = aliens[j].y;
                }
            }
            sol += aliens[i].d;
            for (int j = 0; j < used.size(); j++)
                aliens[used[j]].x = -1;
        }

        printf("%d\n", sol);
    }
    return 0;
}
