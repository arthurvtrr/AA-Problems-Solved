#include <stdio.h>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

vector < pair < int, int > > notes;

int main() {
    int n, m;
    bool f = false;
    scanf("%d %d", &n, &m);
    int x = 0, y = 0, lx = 0, ly = 0;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        if (i == 0) lx = x, ly = y;
        if (abs(y - ly) > abs(x - lx)) f = true;
        lx = x, ly = y;
        notes.push_back(make_pair(x,y));
    }

    if (f) printf("IMPOSSIBLE\n");
    else {
        int max = 0, l = notes[0].first, lh = notes[0].second;
        for (pair < int, int > p : notes) {
            if (max < (abs(p.first + p.second - (l - lh)) / 2)) max = abs(p.first + p.second - (l - lh)) / 2;
            l = p.first, lh = p.second;
        }

        printf("%d\n", max);
    }

    return 0;
}
