#include <bits/stdc++.h>

using namespace std;

#define pii pair < int, int >

int n, q;
vector < int > graph[2020];
set < pii > edges;

struct subset {
    int p, r;
} subs[2020];

int Find(int x) {
    if (x != subs[x].p) subs[x].p = Find(subs[x].p);
    return subs[x].p;
}

void Union(int x, int y) {
    int rx = Find(x), ry = Find(y);
    if (subs[rx].r < subs[ry].r) {
        subs[rx].p = ry;
    }
    else if (subs[rx].r > subs[ry].r) {
        subs[ry].p = rx;
    }
    else {
        subs[ry].p = rx;
        subs[rx].r++;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i <= n; i++) {
        subs[i].p = i;
        subs[i].r = 1;
    }

    vector < pii > aux;

    for (int i = 1; i <= n; i++)
        for (int j = i+1; j <= n; j++)
            aux.push_back(pii(i, j));

    random_shuffle(aux.begin(), aux.end());

    for (pii p : aux) {
        int i = p.first; j = p.second;
        if (Find(i) == Find(j)) continue;

        int a = i, b = j;

        for (int u = 1; u <= n; u++) {
            if (u == a || u == b) continue;
            printf("Q %d %d %d\n", a, u, b);
            fflush(stdout);
            scanf("%d", &q);

            if (q == u) {
                if (Find(a) == Find(u)) a = u;
                else if (Find(b) == Find(u)) b = u;
            }
        }

        int c = a, d = b;

        while (Find(c) != Find(d)) {
            for (int u = 1; u <= n; u++) {
                if (u == a || u == b) continue;

                printf("Q %d %d %d\n", a, u, b);
                fflush(stdout);
                scanf("%d", &q);

                if (q == u) b = u;
            }
            graph[a].push_back(b);
            graph[b].push_back(a);
            edges.insert(pii(min(a, b), max(a, b)));
            Union(a, b);

            a = b; b = d;
        }
    }

    printf("A\n");
    for (pii e : edges)
        printf("%d %d\n", e.first, e.second);
    fflush(stdout);

    return 0;
}


