#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>

using namespace std;

#define INF 1000000

int t, n, m;

string s;
vector < string > names, level[110];
vector < string > msgs, aux;
set < string > chat;

int dist[110][110];
pair < int, int > previous[110][110];

void bfs() {
    for (int i = 0; i < 110; i++)
        for (int j = 0; j < 110; j++) {
            dist[i][j] = INF;
            previous[i][j] = make_pair(-1, -1);
        }

    queue < pair < int, int > > fila;

    for (int i = 0; i < level[0].size(); i++) {
        fila.push(make_pair(0, i));
        dist[0][i] = 0;
    }

    while (!fila.empty()) {
        pair < int, int > u = fila.front();
        fila.pop();

        for (int i = 0; i < level[u.first+1].size(); i++) {
            if (dist[u.first+1][i] > dist[u.first][u.second] + 1 && level[u.first+1][i] != level[u.first][u.second]) {
                dist[u.first+1][i] = dist[u.first][u.second] + 1;
                previous[u.first+1][i] = make_pair(u.first, u.second);
                fila.push(make_pair(u.first+1, i));
            }
        }
    }

    for (int i = 0; i < level[m-1].size(); i++)
        if (dist[m-1][i] == m-1) {
            pair < int, int > ind = make_pair(m-1, i);
            while (ind != make_pair(-1, -1)) {
                aux.push_back(level[ind.first][ind.second]);
                ind = previous[ind.first][ind.second];
            }
            break;
        }

    reverse(aux.begin(), aux.end());
}

int main() {
    scanf("%d", &t);

    for (int tc = 0; tc < t; tc++) {
        names.clear();
        msgs.clear();
        aux.clear();
        for (int i = 0; i < 110; i++)
            level[i].clear();

        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            cin >> s;
            names.push_back(s);
        }

        scanf("%d ", &m);
        for (int i = 0; i < m; i++) {
            getline(cin, s);
            msgs.push_back(s);
            s += '!';

            string x = "";
            int pos = 0;
            while (s[pos] != ':') {
                x += s[pos];
                pos++;
            }

            if (x != "?") {
                level[i].push_back(x);
                continue;
            }
            else {
                chat.clear();

                x = "";
                for (int j = pos; j < s.size(); j++)
                    if (s[j] != ':' && s[j] != '.' && s[j] != ',' && s[j] != '!' && s[j] != '?' && s[j] != ' ') x += s[j];
                    else if (x.size() > 0) {
                        chat.insert(x);
                        x = "";
                    }

                for (int j = 0; j < n; j++)
                    if (!chat.count(names[j]))
                        level[i].push_back(names[j]);
            }
        }

        bfs();

        if (aux.size() != m) printf("Impossible\n");
        else {
            for (int i = 0; i < m; i++) {
                cout << aux[i];
                int pos = 0;
                while (msgs[i][pos] != ':')
                    pos++;

                for (int j = pos; j < msgs[i].size(); j++)
                    printf("%c", msgs[i][j]);
                printf("\n");
            }
        }
    }

    return 0;
}
