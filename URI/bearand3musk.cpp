#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

struct musk {
    int f[4400];
    int total = -2;
} musks[4400];

struct team {
    int a;
    int b;
    int c;
};

int main() {
    int n, m, x, y;
    scanf("%d %d", &n, &m);

    vector < team > teams;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        for (int j = 0; j < 4040; j++)
            if (musks[x].f[j] > 0 && musks[y].f[j] > 0)
                teams.push_back((team) {j, x, y});

        musks[x].f[y]++, musks[y].f[x]++;
        musks[x].total++, musks[y].total++;
    }

    if (teams.size() == 0) printf("-1\n");
    else {
        int sol = 10000;
        for (int i = 0; i < teams.size(); i++)
            sol = min(sol, musks[teams[i].a].total + musks[teams[i].b].total + musks[teams[i].c].total);
        printf("%d\n", sol);
    }
    return 0;
}
