#include <bits/stdc++.h>

using namespace std;

#define INF 1000000000

int r, c;
char grid[55][55];
map < char, int > pos;
int dist[55][55];
string s;

int main() {
    for (int i = 0; i < 55; i++)
        for (int j = 0; j < 55; j++)
            dist[i][j] = (i == j? 0 : INF);

    int cnt = 0;
    for (char i = '0'; i <= '9'; i++)
        pos[i] = cnt++;
    for (char i = 'A'; i <= 'Z'; i++)
        pos[i] = cnt++;
    pos['*'] = cnt++;
    pos['-'] = cnt++;

    scanf("%d %d", &r, &c);

    for (int i = 0; i < r; i++)
        scanf("%s", grid[i]);

    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++) {
            if (i > 0 && grid[i-1][j] != grid[i][j]) dist[pos[grid[i][j]]][pos[grid[i-1][j]]] = 1;
            if (i+1 < r && grid[i+1][j] != grid[i][j]) dist[pos[grid[i][j]]][pos[grid[i+1][j]]] = 1;
            if (j > 0 && grid[i][j-1] != grid[i][j]) dist[pos[grid[i][j]]][pos[grid[i][j-1]]] = 1;
            if (j+1 < c && grid[i][j+1] != grid[i][j]) dist[pos[grid[i][j]]][pos[grid[i][j+1]]] = 1;
        }

    for (int k = 0; k < cnt; k++)
        for (int i = 0; i < cnt; i++)
            for (int j = 0; j < cnt; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    cin >> s;
    int ans = 0, atual = pos[grid[0][0]];
    for (int i = 0; i < s.size(); i++) {
        ans += dist[atual][pos[s[i]]] + 1;
        atual = pos[s[i]];
    }
    ans += dist[atual][pos['*']] + 1;
    printf("%d\n", ans);

    return 0;
}

