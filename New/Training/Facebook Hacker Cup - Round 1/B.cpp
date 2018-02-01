#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>

using namespace std;

int t, n;
long long r;

struct point {
    long long x, y;
} points[55];

vector < int > square[220];
bool found[55];

int main() {
    scanf("%d", &t);
    for (int tc = 0; tc < t; tc++) {
        for (int i = 0; i < 220; i++)
            square[i].clear();

        scanf("%d %lld", &n, &r);
        for (int i = 0; i < n; i++)
            scanf("%lld %lld", &points[i].x, &points[i].y);

        int ind = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                if (points[j].x >= points[i].x - r && points[j].x <= points[i].x
                    && points[j].y >= points[i].y - r && points[j].y <= points[i].y)
                    square[ind].push_back(j);
            ind++;

            for (int j = 0; j < n; j++)
                if (points[j].x >= points[i].x - r && points[j].x <= points[i].x
                    && points[j].y >= points[i].y && points[j].y <= points[i].y + r)
                    square[ind].push_back(j);
            ind++;

            for (int j = 0; j < n; j++)
                if (points[j].x >= points[i].x && points[j].x <= points[i].x + r
                    && points[j].y >= points[i].y - r && points[j].y <= points[i].y)
                    square[ind].push_back(j);
            ind++;

            for (int j = 0; j < n; j++)
                if (points[j].x >= points[i].x && points[j].x <= points[i].x + r
                    && points[j].y >= points[i].y && points[j].y <= points[i].y + r)
                    square[ind].push_back(j);
            ind++;
        }

        int sol = 0;

        for (int i = 0; i < 220; i++)
            for (int j = i+1; j < 220; j++) {
                for (int k = 0; k < 55; k++) found[k] = false;

                for (int k = 0; k < square[i].size(); k++)
                    found[square[i][k]] = true;
                for (int k = 0; k < square[j].size(); k++)
                    found[square[j][k]] = true;

                int cont = 0;
                for (int k = 0; k < 55; k++) cont += found[k];
                sol = max(sol, cont);
            }

        printf("Case #%d: %d\n", tc+1, sol);
    }

    return 0;
}
