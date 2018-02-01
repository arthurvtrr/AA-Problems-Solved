#include <bits/stdc++.h>

using namespace std;

int n;
string a, b;
map < string, int > cnt, ind;
map < int, string > rev;
string club[1010];

struct team {
    string first;
    string sec;
} teams[1010];

bool adj_mat[1010][2020], seen[2020];
int matchR[2020];

bool match_vertex(int u) {
    for (int v = 0; v < 2020; v++) {
        if (adj_mat[u][v] && !seen[v]) {
            seen[v] = true;

            if (matchR[v] < 0 || match_vertex(matchR[v])) {
                matchR[v] = u;
                return true;
            }
        }
    }
    return false;
}

int max_match() {
    memset(matchR, -1, sizeof(matchR));

    int result = 0;
    for (int u = 0; u < 1010; u++) {
        memset(seen, 0, sizeof(seen));

        if (match_vertex(u)) result++;
    }
    return result;
}


int main() {
    scanf("%d", &n);

    int aux = 1;
    for (int i = 0; i < n; i++) {
        cin >> a >> b;
        string f = "", s = "";
        f += a[0];
        f += a[1];
        f += a[2];
        s += a[0];
        s += a[1];
        s += b[0];

        teams[i].first = f;
        teams[i].sec = s;

        cnt[teams[i].first]++;

        if (!ind.count(teams[i].first)) {
            rev[aux] = teams[i].first;
            ind[teams[i].first] = aux++;
        }
        if (!ind.count(teams[i].sec)) {
            rev[aux] = teams[i].sec;
            ind[teams[i].sec] = aux++;
        }
    }

    for (int i = 0; i < n; i++) {
        adj_mat[i][ind[teams[i].sec]] = 1;
        if (cnt[teams[i].first] == 1)
            adj_mat[i][ind[teams[i].first]] = 1;
    }

    int match = max_match();

    if (match < n) printf("NO\n");
    else {
        printf("YES\n");
        for (int i = 0; i < 2020; i++)
            if (matchR[i] != -1)
                club[matchR[i]] = rev[i];

        for (int i = 0; i < n; i++)
            cout << club[i] << endl;
    }

    return 0;
}

