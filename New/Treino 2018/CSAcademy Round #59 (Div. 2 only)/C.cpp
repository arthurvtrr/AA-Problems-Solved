#include <bits/stdc++.h>

using namespace std;

int n;
char grid[3030][3030];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)
            scanf(" %c", &grid[i][j]);

    set < int > pos, aux;
    string ans = "";
    ans += grid[1][1];
    pos.insert(1);
    for (int i = 1; i < n; i++) {
        char best = 'z';
        for (int v : pos) {
            best = min(best, grid[i+1][v]);
            best = min(best, grid[i+1][v+1]);
        }
        aux.clear();

        for (int v : pos) {
            if (grid[i+1][v] == best) aux.insert(v);
            if (grid[i+1][v+1] == best) aux.insert(v+1);
        }
        pos = aux;
        ans += best;
    }
    cout << ans << endl;

    return 0;
}
