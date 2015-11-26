#include <bits/stdc++.h>

using namespace std;

#define INF 1000000000

int flow(int ini, int fim, int n, vector < int > *graph, int **cap) {
    int answer = 0;
    int previous[n];
    bool used[n];

    while(true) {
        fill(used, used+n, false);
        fill(previous, previous+n, -1);

        queue < int > fila;
        fila.push(ini);

        while(!fila.empty()) {
            int u = fila.front();
            used[u] = true;
            fila.pop();

            for(int v : graph[u])
                if(!used[v] and cap[u][v] > 0) {
                    previous[v] = u;
                    fila.push(v);
                }
        }

        if (previous[fim] == -1) break;
        int minimum = INT_MAX, u = fim;

        while (previous[u] != -1) {
            minimum = min(cap[previous[u]][u], minimum);
            u = previous[u];
        }

        answer += minimum;
        u = fim;

        while (previous[u] != -1) {
            cap[previous[u]][u] -= minimum;
            cap[u][previous[u]] += minimum;
            u = previous[u];
        }
    }

    return answer;
}

#define ini 53
#define fim 54

int main() {
    string s;

    while (getline(cin, s)) {
        vector < int > connections[55];
        int **cap = new int*[55];
        for (int i = 0; i < 55; i++)
            cap[i] = new int[55];

        for (int i = 0; i < 55; i++)
            for (int j = 0; j < 55; j++)
                cap[i][j] = 0;

        int sum = 0;

        while (!s.empty()) {
            connections[s[0] - '0'].push_back(fim);
            connections[fim].push_back(s[0] - '0');
            cap[s[0] - '0'][fim] = s[1] - '0';
            sum += s[1] - '0';

            for (int i = 3;; i++) {
                if (s[i] == ';') break;

                connections[s[i] - '0'].push_back(s[0] - '0');
                connections[s[0] - '0'].push_back(s[i] - '0');
                cap[s[i] - '0'][s[0] - '0'] = 1;
            }

            for (int i = 0; i <= 9; i++) {
                connections[ini].push_back(i);
                connections[i].push_back(ini);
                cap[ini][i] = 1;
            }

            getline(cin, s);
        }

        int sol = flow(ini, fim, 55, connections, cap);

        if (sol != sum) printf("!\n");
        else {
            for (int i = 0; i <= 9; i++) {
                bool f = false;
                for (int j = 17; j <= 42; j++)
                    if (cap[j][i] == 1) {
                        cout << (char)(j + '0');
                        f = true;
                        break;
                    }
                if (!f) printf("_");
            }

            printf("\n");
        }
    }
    return 0;
}
