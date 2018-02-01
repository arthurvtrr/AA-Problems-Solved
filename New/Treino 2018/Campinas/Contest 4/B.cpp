#include <bits/stdc++.h>

using namespace std;

bool grid[100][100];

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
string mv[4] = {"NORTH", "SOUTH", "WEST", "EAST"};
string inv[4] = {"SOUTH", "NORTH", "EAST", "WEST"};

void dfs(int x, int y) {
    grid[x][y] = true;
    for (int i = 0; i < 4; i++) {
        if (x+dx[i] >= 0 && x+dx[i] < 100 && y+dy[i] >= 0 && y+dy[i] < 100 && !grid[x+dx[i]][y+dy[i]]) {
            cout << mv[i] << endl;
            fflush(stdout);
            string ret;
            cin >> ret;

            if (ret == "BLOCKED") grid[x+dx[i]][y+dy[i]] = true;
            else {
                dfs(x+dx[i], y+dy[i]);
                cout << inv[i] << endl;
                fflush(stdout);
                string ret;
                cin >> ret;
            }
        }
    }
}

int main() {
    dfs(50, 50);
    cout << "DONE" << endl;
    fflush(stdout);

    return 0;
}

