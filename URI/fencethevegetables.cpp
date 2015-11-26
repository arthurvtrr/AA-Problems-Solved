#include <stdio.h>
#include <algorithm>
#include <vector>
#include <set>
#include <map>

using namespace std;

#define pii pair < int, int >

struct point {
    int y;
    int t;
};

struct line {
    long long h;
    long long l;
};

set < pii > pos;
vector < point > X[330000];
map < int, int > ind;
map < int, int > inv;
line lines[330000];

long long solve() {
    int last = -1000;
    for (int i = 0; i < 301000; i++)
        if (X[i].size() && X[i][X[i].size()-1].y >= last) {
            last = X[i][X[i].size()-1].y;
            X[i][X[i].size()-1].t = 1;
        }

    last = -1000;
    for (int i = 301000; i >= 0; i--)
        if (X[i].size()) {
            if (X[i][X[i].size()-1].t == 1) break;
            else if (X[i][X[i].size()-1].y >= last) {
                last = X[i][X[i].size()-1].y;
                X[i][X[i].size()-1].t = 1;
            }
        }

    last = 1000000000;
    for (int i = 0; i < 301000; i++)
        if (X[i].size() && X[i][0].y <= last) {
            last = X[i][0].y;
            X[i][0].t = 1;
        }

    last = 1000000000;
    for (int i = 301000; i >= 0; i--)
        if (X[i].size()) {
            if (X[i][0].t == 1) break;
            else if (X[i][0].y <= last) {
                last = X[i][0].y;
                X[i][0].t = 1;
            }
        }

    lines[0].h = X[0][X[0].size()-1].y;
    lines[0].l = X[0][0].y;

    int aux = 1;
    for (int i = 1; i < 301000; i++)
        if (X[i].size()) {
            aux++;
            if (X[i][X[i].size()-1].t == 1) lines[i].h = X[i][X[i].size()-1].y;
            else lines[i].h = lines[i-1].h;

            if (X[i][0].t == 1) lines[i].l = X[i][0].y;
            else lines[i].l = lines[i-1].l;
        }

    for (int i = aux-2; i >= 0; i--) {
        if (X[i].size()) {
            if (X[i][X[i].size()-1].t == 1) lines[i].h = X[i][X[i].size()-1].y;
            else lines[i].h = min(lines[i].h, lines[i+1].h);

            if (X[i][0].t == 1) lines[i].l = X[i][0].y;
            else lines[i].l = max(lines[i].l, lines[i+1].l);
        }
    }

    long long area = 0LL;

    for (int i = 1; i < aux; i++)
        if (X[i].size()) {
            if (lines[i].h >= lines[i-1].h && lines[i].l <= lines[i-1].l)
                area += (lines[i-1].h - lines[i-1].l) * (inv[i] - inv[i-1]);
            else if (lines[i].h <= lines[i-1].h && lines[i].l >= lines[i-1].l)
                area += (lines[i].h - lines[i].l) * (inv[i] - inv[i-1]);
            else if (lines[i].h > lines[i-1].h && lines[i].l > lines[i-1].l)
                area += (lines[i-1].h - lines[i].l) * (inv[i] - inv[i-1]);
            else if (lines[i].h < lines[i-1].h && lines[i].l < lines[i-1].l)
                area += (lines[i].h - lines[i-1].l) * (inv[i] - inv[i-1]);
            else if (lines[i].l >= lines[i-1].h)
                area += (lines[i].l - lines[i-1].h + 1) * (inv[i] - inv[i-1]);
            else
                area += (lines[i-1].l - lines[i].h + 1) * (inv[i] - inv[i-1]);

            if (i > 1 && lines[i].l >= lines[i-2].h)
                area += (lines[i].l - lines[i-2].h + 1) * (inv[i-1] - inv[i-2]);
            else if (i > 1 && lines[i].h <= lines[i-2].l)
                area += (lines[i-2].l - lines[i].h + 1) * (inv[i-1] - inv[i-2]);
        }

    return area;
}

int main() {
    int v, x, y;
    while (scanf("%d", &v) != EOF) {
        pos.clear();
        ind.clear();
        inv.clear();
        for (int i = 0; i < 310000; i++) {
            X[i].clear();
            lines[i].h = 0LL;
            lines[i].l = 0LL;
        }

        for (int i = 0; i < v; i++) {
            scanf("%d %d", &x, &y);
            for (int j = -1; j <= 1; j++)
                for (int k = -1; k <= 1; k++)
                    pos.insert(make_pair(x+j,y+k));
        }

        int cnt = 0;
        for (set < pii >::iterator it = pos.begin(); it != pos.end(); it++) {
            if (!ind.count(it->first)) {
                ind[it->first] = cnt;
                inv[cnt++] = it->first;
            }
            X[ind[it->first]].push_back((point) {it->second, 0});
        }

        int min_x = 1000000000, max_x = -1000, min_y = 1000000000, max_y = -1000;
        for (int i = 0; i < 301000; i++)
            if (X[i].size()) {
                if (inv[i] < min_x) min_x = inv[i];
                if (inv[i] > max_x) max_x = inv[i];
                if (X[i][0].y < min_y) min_y = X[i][0].y;
                if (X[i][X[i].size()-1].y > max_y) max_y = X[i][X[i].size()-1].y;
            }

        int perim = (max_x - min_x) * 2 + (max_y - min_y) * 2;
        printf("%d %lld\n", perim, solve());
    }
    return 0;
}
