#include <stdio.h>
#include <vector>

using namespace std;

int freqVizinhos[110000];

int main() {
    vector < int > graph[110000];
    int n, m, x, y;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    for (int i = 1; i <= n; i++)
        freqVizinhos[graph[i].size()]++;

    if (freqVizinhos[1] == 2 && freqVizinhos[2] == n-2) printf("bus topology\n");
    else if (freqVizinhos[2] == n) printf("ring topology\n");
    else if (freqVizinhos[n-1] == 1 && freqVizinhos[1] == n-1) printf("star topology\n");
    else printf("unknown topology\n");

    return 0;
}
