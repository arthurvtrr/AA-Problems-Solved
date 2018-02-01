#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>
#include <map>
#include <stack>

using namespace std;

#define N 200200
#define pii pair < int, int >

int t, n, k, acum[N], left[N], right[N];

struct jewel {
    int x, y, c;
} jewels[N];

map < int, int > ind;
vector < pii > colors[N];
vector < int > pos[N];

vector < int > seg[4*N];

void build(int id, int ini, int fim) {
    if (ini == fim) {
        seg[id] = pos[ini];
        return;
    }

    int meio = (ini + fim) / 2;

    build(2*id, ini, meio);
    build(2*id+1, meio+1, fim);

    int a = 0, b = 0;
    while (a < seg[2*id].size() && b < seg[2*id+1].size()) {
        if (seg[2*id][a] < seg[2*id+1][b])
            seg[id].push_back(seg[2*id][a++]);
        else
            seg[id].push_back(seg[2*id+1][b++]);
    }

    while (a < seg[2*id].size())
        seg[id].push_back(seg[2*id][a++]);

    while (b < seg[2*id+1].size())
        seg[id].push_back(seg[2*id+1][b++]);
}

int query(int id, int ini, int fim, int start, int end, int h) {
    if (ini > end || fim < start)
        return 0;
    if (start <= ini && end >= fim) {
        int l = 0, r = seg[id].size()-1;

        while (l <= r) {
            int mid = (l + r) / 2;

            if (seg[id][mid] >= h) r = mid-1;
            else l = mid+1;
        }

        return l;
    }

    int meio = (ini + fim) / 2;

    return query(2*id, ini, meio, start, end, h) + query(2*id+1, meio+1, fim, start, end, h);
}

bool cmp(pii a, pii b) {
    if (a.first == b.first)
        return a.second > b.second;
    return a.first < b.first;
}

int main() {
    scanf("%d", &t);

    for (int tc = 0; tc < t; tc++) {

        for (int i = 0; i < N; i++) {
            acum[i] = left[i] = right[i] = 0;
            colors[i].clear();
            pos[i].clear();
        }
        ind.clear();
        for (int i = 0; i < 4*N; i++)
            seg[i].clear();

        scanf("%d %d", &n, &k);

        for (int i = 0; i < n; i++) {
            scanf("%d %d %d", &jewels[i].x, &jewels[i].y, &jewels[i].c);
            ind[jewels[i].x];
        }

        int coord = 1;
        for (map < int, int >::iterator it = ind.begin(); it != ind.end(); it++)
            it->second = coord++;

        for (int i = 0; i < n; i++) {
            jewels[i].x = ind[jewels[i].x];
            colors[jewels[i].c].push_back(make_pair(jewels[i].x, jewels[i].y));
            acum[jewels[i].x]++;
            pos[jewels[i].x].push_back(jewels[i].y);
        }

        for (int i = 1; i < N; i++)
            acum[i] += acum[i-1];

        int sol = 0;

        for (int i = 1; i <= k; i++) {
            sort(colors[i].begin(), colors[i].end());

            sol = max(sol, acum[colors[i][0].first-1] - acum[0]);

            for (int j = 0; j < (int)colors[i].size() - 1; j++)
                if (colors[i][j+1].first != colors[i][j].first)
                    sol = max(sol, acum[colors[i][j+1].first-1] - acum[colors[i][j].first]);

            sol = max(sol, acum[N-1] - acum[colors[i][(int)colors[i].size() - 1].first]);
        }

        for (int i = 0; i < N; i++)
            sort(pos[i].begin(), pos[i].end());

        build(1, 1, N-1);

        stack < pii > aux;

        for (int i = 1; i <= k; i++) {
            int last = 0;
            while (aux.size()) aux.pop();
            aux.push(make_pair(0, 0));

            for (int j = 0; j < (int)colors[i].size(); j++)
                if (colors[i][j].first != last) {
                    while (colors[i][j].second <= aux.top().second)
                        aux.pop();

                    left[colors[i][j].first] = aux.top().first;
                    aux.push(colors[i][j]);
                    last = colors[i][j].first;
                }

            sort(colors[i].begin(), colors[i].end(), cmp);
            last = N;
            while (aux.size()) aux.pop();
            aux.push(make_pair(N, 0));

            for (int j = (int)colors[i].size() - 1; j >= 0; j--)
                if (colors[i][j].first != last) {
                    while (colors[i][j].second <= aux.top().second)
                        aux.pop();

                    right[colors[i][j].first] = aux.top().first;
                    aux.push(colors[i][j]);
                    last = colors[i][j].first;
                }

            sort(colors[i].begin(), colors[i].end());
            last = 0;
            for (int j = 0; j < (int)colors[i].size(); j++)
                if (colors[i][j].first != last) {
                    sol = max(sol, query(1, 1, N-1, left[colors[i][j].first]+1, right[colors[i][j].first]-1, colors[i][j].second));
                    last = colors[i][j].first;
                }
        }

        printf("%d\n", sol);
    }

    return 0;
}
