#include <bits/stdc++.h>

using namespace std;

int n, m, inix, iniy;
char grid[55][55];
string s;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%s", grid[i]);
    cin >> s;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'S') { inix = i, iniy = j; }
        }

    vector < int > aux = {0, 1, 2, 3};

    int ans = 0;
    do {
        int x = inix, y = iniy;
        for (int i = 0; i < s.size(); i++) {
            x += dx[aux[s[i] - '0']];
            y += dy[aux[s[i] - '0']];

            if (x < 0 || x >= n || y < 0 || y >= m) break;
            if (grid[x][y] == '#') break;
            if (grid[x][y] == 'E') { ans++; break; }
        }
    } while (next_permutation(aux.begin(), aux.end()));

    printf("%d\n", ans);

    return 0;
}
