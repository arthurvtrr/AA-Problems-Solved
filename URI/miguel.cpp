#include <stdio.h>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>

#define INF 1000000000

using namespace  std;

void Dijkstra(map < char, vector < pair < char, int > > > sy, map < char, vector < pair < char, int > > > sm, map < char, pair < int, int > > app, map < char, int > dy, map < char, int > dm, char s, char f) {
    priority_queue < pair < int, int > > fila;
    map < char, bool > visited;
    dy[s] = 0;
    fila.push(make_pair(-dy[s], s));

    while (!fila.empty()) {
        int u = fila.top().second;
        visited[u] = true;
        fila.pop();

        for (pair < char, int > v : sy[u]) {
            if (!visited[v.first] && dy[v.first] > dy[u] + v.second) {
                dy[v.first] = dy[u] + v.second;
                fila.push(make_pair(-dy[v.first], v.first));
            }
        }
    }

    visited.clear();
    dm[f] = 0;
    fila.push(make_pair(-dm[f], f));
    visited[f] = true;

    while (!fila.empty()) {
        int u = fila.top().second;
        fila.pop();

        for (pair < char, int > v : sm[u]) {
            if (!visited[v.first] && dm[v.first] > dm[u] + v.second) {
                dm[v.first] = dm[u] + v.second;
                fila.push(make_pair(-dm[v.first], v.first));
                visited[v.first] = true;
            }
        }
    }

    int sol = INF;
    vector < char > pos;
    for(map < char, pair < int, int > >::iterator it = app.begin(); it != app.end(); it++) {
        if (it->second.first > 0 && it->second.second > 0) {
            if (dy[it->first] + dm[it->first] < sol) {
                pos.clear();
                sol = dy[it->first] + dm[it->first];
                pos.push_back(it->first);
            }
            else if (dy[it->first] + dm[it->first] == sol)
                pos.push_back(it->first);
        }
    }

    if (sol == INF) printf("You will never meet.\n");
    else {
        printf("%d", sol);
        sort(pos.begin(), pos.begin()+pos.size());
        for (char c : pos) {
            printf(" %c", c);
        }
        printf("\n");
    }
}

int main() {
    int n, w;
    char g, t, x, y, s, f;
    while (scanf("%d%*c", &n) && n != 0) {
        map < char, vector < pair < char, int > > > streetsy;
        map < char, vector < pair < char, int > > > streetsm;
        map < char, pair < int, int > > appears;
        map < char, int > disty;
        map < char, int > distm;
        for (int i = 0; i < n; i++) {
            scanf("%c %c %c %c %d%*c", &g, &t, &x, &y, &w);
            if (g == 'Y' && t == 'U') {
                streetsy[x].push_back(make_pair(y, w));
                appears[x].first++;
                appears[y].first++;
                disty[x] = INF, disty[y] = INF;
            }
            else if (g == 'Y') {
                streetsy[x].push_back(make_pair(y, w));
                streetsy[y].push_back(make_pair(x, w));
                appears[x].first++;
                appears[y].first++;
                disty[x] = INF, disty[y] = INF;
            }
            else if (g == 'M' && t == 'U') {
                streetsm[x].push_back(make_pair(y, w));
                appears[x].second++;
                appears[y].second++;
                distm[x] = INF, distm[y] = INF;
            }
            else {
                streetsm[x].push_back(make_pair(y, w));
                streetsm[y].push_back(make_pair(x, w));
                appears[x].second++;
                appears[y].second++;
                distm[x] = INF, distm[y] = INF;
            }
        }

        scanf("%c %c%*c", &s, &f);
        appears[s].first++, appears[f].second++;
        disty[s] = INF, distm[f] = INF;
        Dijkstra(streetsy, streetsm, appears, disty, distm, s, f);
    }

    return 0;
}
