#include <bits/stdc++.h>

using namespace std;

#define piv pair < int, vector < int > >
#define pii pair < int, int >

int n;
string s;
vector < vector < int > > lists[1010];
vector < piv > aux;

bool cmp(piv a, piv b) {
    if (a.second.size() == b.second.size())
        return a.second < b.second;
    return a.second.size() < b.second.size();
}

struct subset {
    int parent, rank;
} subsets[1010];

int Find(int x) {
    if (x != subsets[x].parent)
        subsets[x].parent = Find(subsets[x].parent);
    return subsets[x].parent;
}

void Union(int x, int y) {
    int rx = Find(x), ry = Find(y);
    if (subsets[rx].rank < subsets[ry].rank) subsets[rx].parent = ry;
    else if (subsets[rx].rank > subsets[ry].rank) subsets[ry].parent = rx;
    else {
        subsets[ry].parent = rx;
        subsets[rx].rank++;
    }
}

vector < int > visited, graph[1010];

void dfs(int u, int p) {
    visited.push_back(u);
    for (int v : graph[u])
        if (v != p)
            dfs(v, u);
}

int app[1010][1010];
bool neigh[1010];

int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        cin >> s;
        vector < int > x;
        int siz = 0, val, pos = 0;

        while (pos < s.size()) {
            if (s[pos] >= '0' && s[pos] <= '9') {
                if (siz == 0) {
                    if (x.size()) {
                        lists[i].push_back(x);
                        aux.push_back(piv(i, x));
                    }
                    x.clear();

                    while (pos < s.size() && s[pos] != ':') {
                        siz *= 10;
                        siz += s[pos] - '0';
                        pos++;
                    }
                }
                else {
                    val = 0;
                    while (pos < s.size() && s[pos] != ',' && s[pos] != '-') {
                        val *= 10;
                        val += s[pos] - '0';
                        pos++;
                    }
                    x.push_back(val);
                    siz--;
                }
            }
            else pos++;
        }

        if (x.size()) {
            lists[i].push_back(x);
            aux.push_back(piv(i, x));
        }

        for (int j = 0; j < lists[i].size(); j++)
            sort(lists[i][j].begin(), lists[i][j].end());

        sort(lists[i].begin(), lists[i].end());

        for (int j = 0; j < lists[i].size(); j++)
            for (int k = 0; k < lists[i][j].size(); k++)
                app[lists[i][j][k]][i] = j;
    }

    sort(aux.begin(), aux.end(), cmp);

    for (int i = 1; i <= n; i++) {
        subsets[i].parent = i;
        subsets[i].rank = 1;
    }

    vector < pii > edges;
    for (int i = 0; i < aux.size(); i++) {
        if (Find(aux[i].first) == Find(aux[i].second[0])) continue;

        for (int j = 0; j < 1010; j++)
            neigh[j] = false;
        for (int v : aux[i].second)
            neigh[v] = true;

        int best;
        for (int v : aux[i].second) {
            bool f = true;
            for (int j = 0; j < lists[v][app[aux[i].first][v]].size(); j++)
                if (neigh[lists[v][app[aux[i].first][v]][j]])
                    f = false;
            if (f) best = v;
        }

        Union(aux[i].first, best);
        edges.push_back(pii(aux[i].first, best));
        graph[aux[i].first].push_back(best);
        graph[best].push_back(aux[i].first);
    }

    bool valid = true;

    for (int i = 1; i <= n; i++) {
        vector < vector < int > > x;
        for (int v : graph[i]) {
            visited.clear();
            dfs(v, i);
            sort(visited.begin(), visited.end());
            x.push_back(visited);
        }
        sort(x.begin(), x.end());
        if (x != lists[i])
            valid = false;
    }

    if (!valid) printf("-1\n");
    else {
        printf("%d\n", n-1);
        for (pii v : edges)
            printf("%d %d\n", v.first, v.second);
    }

    return 0;
}
