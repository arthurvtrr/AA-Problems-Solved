#include <bits/stdc++.h>

using namespace std;

int h, w;
char grid[220][220];
string s, aux;
map < char, string > val = {{'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
                            {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
                            {'8', "1000"}, {'9', "1001"}, {'a', "1010"}, {'b', "1011"},
                            {'c', "1100"}, {'d', "1101"}, {'e', "1110"}, {'f', "1111"}};

bool visited[2][220][220];
int cx[4] = {-1, 1, 0, 0};
int cy[4] = {0, 0, -1, 1};

bool valid(int x, int y, int i, int t) {
    if (x + cx[i] < 0 || x + cx[i] > h+1) return false;
    if (y + cy[i] < 0 || y + cy[i] > 4*w+1) return false;
    if (t == 0 && grid[x+cx[i]][y+cy[i]] != grid[x][y]) return false;
    if (visited[1][x+cx[i]][y+cy[i]]) return false;
    return true;
}

void dfs(int x, int y, int t) {
    if (t == 0) visited[0][x][y] = true;
    visited[1][x][y] = true;

    for (int i = 0; i < 4; i++)
        if (valid(x, y, i, t))
            dfs(x+cx[i], y+cy[i], t);
}

int main() {
    int t = 1;
    while (1) {
        scanf("%d %d", &h, &w);
        if (h + w == 0) break;

        for (int i = 0; i < 220; i++)
            for (int j = 0; j < 220; j++) {
                grid[i][j] = '0';
                visited[0][i][j] = visited[1][i][j] = false;
            }

        for (int i = 0; i < h; i++) {
            cin >> s;
            aux = "";
            for (int j = 0; j < w; j++)
                aux += val[s[j]];

            for (int j = 0; j < 4*w; j++)
                grid[i+1][j+1] = aux[j];
        }

        //for (int i = 0; i <= h+1; i++) {
        //    for (int j = 0; j <= 4*w+1; j++)
        //        printf("%c", grid[i][j]);
        //    printf("\n");
        //}

        string ans = "";

        for (int i = 1; i <= h; i++)
            for (int j = 1; j <= 4*w; j++)
                if (grid[i][j] == '1' && !visited[0][i][j]) {
                    dfs(i, j, 0);
                    //printf("%d %d\n", i, j);

                    int cnt = 0;
                    for (int a = 0; a <= h+1; a++)
                        for (int b = 0; b <= 4*w+1; b++)
                            if (grid[a][b] == '0' && !visited[1][a][b]) {
                                //printf("-- %d %d\n", a, b);
                                dfs(a, b, 1);
                                cnt++;
                            }
                    //printf("%d\n", cnt);

                    if (cnt == 2) ans += 'A';
                    else if (cnt == 4) ans += 'J';
                    else if (cnt == 6) ans += 'D';
                    else if (cnt == 5) ans += 'S';
                    else if (cnt == 1) ans += 'W';
                    else ans += 'K';

                    for (int a = 0; a <= h+1; a++)
                        for (int b = 0; b <= 4*w+1; b++)
                            visited[1][a][b] = false;
                }

        sort(ans.begin(), ans.end());
        printf("Case %d: ", t++);
        cout << ans << endl;
    }

    return 0;
}

/*
5 6
007000
00d801
007001
0fff01
007000
*/
