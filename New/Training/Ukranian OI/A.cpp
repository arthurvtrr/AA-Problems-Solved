#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

int n, m;
long long g, s, x, y, gi, si;

struct edge {
    int from;
    int to;
    long long g;
    long long s;
} edges[50500];

bool cmp1(edge a, edge b) {
    return a.g < b.g;
}
bool cmp2(edge a, edge b) {
    return a.s < b.s;
}

struct subset {
    int parent;
    int _rank;
} subsets[220];

int _find(int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = _find(subsets[i].parent);
    return subsets[i].parent;
}

void Union(int x, int y) {
    int xroot = _find(x);
    int yroot = _find(y);

    if (subsets[xroot]._rank < subsets[yroot]._rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot]._rank > subsets[yroot]._rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot]._rank++;
    }
}

int main() {
    scanf("%d %d", &n, &m);
    scanf("%lld %lld", &g, &s);

    for (int i = 0; i < m; i++) {
        scanf("%lld %lld %lld %lld", &x, &y, &gi, &si);
        edges[i].from = x;
        edges[i].to = y;
        edges[i].g = gi;
        edges[i].s = si;
    }

    long long ming = 0, mins = 0, ming1 = 0, mins1 = 0;
    int cont1 = 0, cont2 = 0;

    sort(edges, edges+m, cmp1);

    for (int i = 0; i < 220; i++) {
        subsets[i].parent = i;
        subsets[i]._rank = 1;
    }

    for (int i = 0; i < m; i++) {
        if (_find(edges[i].from) != _find(edges[i].to)) {
            Union(edges[i].from, edges[i].to);
            cont1++;
            ming = edges[i].g;
            mins = max(mins, edges[i].s);
        }
        if (cont1 == n-1)
            break;
    }

    sort(edges, edges+m, cmp2);

    for (int i = 0; i < 220; i++) {
        subsets[i].parent = i;
        subsets[i]._rank = 1;
    }

    for (int i = 0; i < m; i++) {
        if (_find(edges[i].from) != _find(edges[i].to)) {
            Union(edges[i].from, edges[i].to);
            cont2++;
            ming1 = max(ming1, edges[i].g);
            mins1 = edges[i].s;
        }
        if (cont2 == n-1)
            break;
    }

    long long sol = 1000000000000;
    if (cont1 == n-1)
        sol = min(sol, ming * g + mins * s);
    if (cont2 == n-1)
        sol = min(sol, ming1 * g + mins1 * s);

    printf("%lld\n", sol == 1000000000000? -1 : sol);

    return 0;
}
