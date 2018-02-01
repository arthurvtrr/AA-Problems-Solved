#include <bits/stdc++.h>

using namespace std;

#define pii pair <int, int>

int t, w, h, grid[110][110];
vector < pii > moves;

void turn(bool col, int pos) {
    moves.push_back(pii(col, pos));

    if (!col) {
        for (int i = 0; i < w/2; i++)
            swap(grid[pos][i], grid[pos][w-i-1]);
    }
    else {
        for (int i = 0; i < h/2; i++)
            swap(grid[i][pos], grid[h-i-1][pos]);
    }
}

int main() {
    scanf("%d", &t);
    for (int tc = 0; tc < t; tc++) {
        moves.clear();

        scanf("%d %d", &w, &h);
        for (int i = 0; i < h; i++)
            for (int j = 0; j < w; j++)
                scanf("%d", &grid[i][j]);

        int midr = (h+1)/2 - 1, midc = (w+1)/2 - 1;

        if (h % 2 == 1 && grid[midr][0] != midr * w + 1)
            turn(false, midr);

        if (w % 2 == 1 && grid[0][midc] != midc + 1)
            turn(true, midc);

        for (int i = 0; i < h/2; i++)
            for (int j = 0; j < w/2; j++) {
                if (grid[i][j] != i * w + j + 1) {
                    turn(true, j); turn(false, h-i-1);
                    turn(true, j); turn(false, h-i-1);
                }
                if (grid[i][j] != i * w + j + 1) {
                    turn(true, j); turn(false, h-i-1);
                    turn(true, j); turn(false, h-i-1);
                }
                if (grid[i][j] != i * w + j + 1) {
                    turn(false, i); turn(true, j);
                    turn(false, i); turn(true, j);
                }
                if (grid[h-i-1][w-j-1] != (h-i-1) * w + (w-j-1) + 1) {
                    turn(false, h-i-1); turn(true, w-j-1);
                    turn(false, h-i-1); turn(true, w-j-1);
                }
                if (grid[h-i-1][w-j-1] != (h-i-1) * w + (w-j-1) + 1) {
                    turn(false, h-i-1); turn(true, w-j-1);
                    turn(false, h-i-1); turn(true, w-j-1);
                }
                if (grid[h-i-1][j] != (h-i-1) * w + j + 1) {
                    if (j) { turn(false, i); turn(true, j); turn(false, i); }
                    else { turn(true, j); turn(false, i); turn(true, j); }
                }
            }

        bool solved = true;
        for (int i = 0; i < h; i++)
            for (int j = 0; j < w; j++)
                if (grid[i][j] != i * w + j + 1)
                    solved = false;

        if (solved) {
            printf("POSSIBLE %d", moves.size());
            for (int i = 0; i < moves.size(); i++)
                printf(" %c%d", moves[i].first? 'C' : 'R', moves[i].second + 1);
            printf("\n");
        }
        else printf("IMPOSSIBLE\n");

    }
    return 0;
}
